#include "TaskWithTimeControl.h"


CTaskWithTimeControl::CTaskWithTimeControl(const map<int, int> &confs)
{
	m_ConfLims = confs;

	for (const auto& conf : m_ConfLims)
	{
		m_NextSendTime.insert({ conf.first, CTimeInterval() });
	}
}

void CTaskWithTimeControl::AddTask(const Task& task)
{
	if (!ShouldTaskSend(task))
	{
		m_DelayTasks.insert(task);
	}
	else
	{
		m_Tasks.push(task);
		UpdateNextSendTime(task);
	}
}

bool CTaskWithTimeControl::GetTask(Task &task)
{
	if (GetDelayTask(task))
	{
		return true;
	}

	if (m_Tasks.empty())
	{
		return false;
	}
		
	task = m_Tasks.front();
	m_Tasks.pop();

	return true;
}

bool CTaskWithTimeControl::GetDelayTask(Task& task)
{
	for (auto& elem : m_DelayTasks)
	{
		if (ShouldTaskSend(elem))
		{
			task = elem;
			//放入任务队列的时候，更新下请求号，保证发出去的请求号是递增的
			task.RequestNo = Task::GenerateRequestNo();

			m_DelayTasks.erase(elem);
			return true;
		}
	}
	return false;
}

bool CTaskWithTimeControl::ShouldTaskSend(const Task& task) const
{
	//只限制通用请求
	if (task.uType != TASK_REQUEST_COMMON)
		return true;

	//只有在m_NextSendTime的功能号，才需要限制
	auto it = m_NextSendTime.find(task.funcno);
	if (it == m_NextSendTime.end())
		return true;
	
	//允许请求时间是否到
	if (!it->second.ShouldSend())
		return false;

	return true;
}

void CTaskWithTimeControl::UpdateNextSendTime(const Task &task)
{
	if (task.uType != TASK_REQUEST_COMMON)
		return;

	auto confIt = m_ConfLims.find(task.funcno);
	if (confIt == m_ConfLims.end())
		return;

	auto timeInterval = confIt->second;

	auto it = m_NextSendTime.find(task.funcno);
	if (it != m_NextSendTime.end())
	{
		it->second.SetAvailibleTime(timeInterval);
	}
}

bool CTaskWithTimeControl::Empty() const
{
	return m_Tasks.empty() && m_DelayTasks.empty();
}
