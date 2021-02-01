#pragma once

#include "TimeInterval.h"
#include "CommStruct.h"

#include <map>
#include <queue>
#include <set>

using namespace std;



class CTaskWithTimeControl
{
public:
	CTaskWithTimeControl(const map<int, int> &confs);
	~CTaskWithTimeControl() = default;

	void AddTask(const Task& task);

	bool GetTask(Task &task);

	bool Empty() const;
private:
	/**检查该任务是否可以立即发送
	* true : delay ; false : no delay
	*/
	bool ShouldTaskSend(const Task& task) const;

	/*从延迟请求的对列中获取可用任务
	* return  true为获取成功，false为未获取到
	*/
	bool GetDelayTask(Task& task);

	//每次处理任务时，更新任务可处理时间
	void UpdateNextSendTime(const Task &task);
private:
	//任务队列
	std::queue<Task> m_Tasks;
	
	//key = funcno， value = 任务可处理的时间
	//保存功能号下次发送的时间，需要限制的功能号始终存在一条记录
	std::map<int, CTimeInterval> m_NextSendTime;
	
	//delay对列里的任务不能重复
	std::set<Task> m_DelayTasks;

	//key = funcno, value = limTime 毫秒
	std::map<int, int> m_ConfLims;
};