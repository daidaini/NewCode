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
	/**���������Ƿ������������
	* true : delay ; false : no delay
	*/
	bool ShouldTaskSend(const Task& task) const;

	/*���ӳ�����Ķ����л�ȡ��������
	* return  trueΪ��ȡ�ɹ���falseΪδ��ȡ��
	*/
	bool GetDelayTask(Task& task);

	//ÿ�δ�������ʱ����������ɴ���ʱ��
	void UpdateNextSendTime(const Task &task);
private:
	//�������
	std::queue<Task> m_Tasks;
	
	//key = funcno�� value = ����ɴ����ʱ��
	//���湦�ܺ��´η��͵�ʱ�䣬��Ҫ���ƵĹ��ܺ�ʼ�մ���һ����¼
	std::map<int, CTimeInterval> m_NextSendTime;
	
	//delay��������������ظ�
	std::set<Task> m_DelayTasks;

	//key = funcno, value = limTime ����
	std::map<int, int> m_ConfLims;
};