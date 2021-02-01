#include "TaskWithTimeControl.h"
#include "PtkConfs.h"

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

int main()
{
	CPtkConfs::GetInstance().ReadConfigs();
	CTaskWithTimeControl myHandle = CPtkConfs::GetInstance().GetQueryLimitConfig();

	Task one;
	one.funcno = 6014;
	one.uType = TASK_REQUEST_COMMON;
	myHandle.AddTask(one);
	
	Task two;
	two.funcno = 6013;
	two.uType = TASK_QUERY_TRADE;
	myHandle.AddTask(two);

	Task three;
	three.funcno = 9005;
	three.uType = TASK_REQUEST_COMMON;
	myHandle.AddTask(three);

	Task other;
	other.funcno = 6014;
	other.uType = TASK_REQUEST_COMMON;
	myHandle.AddTask(other);

	two.RequestNo = Task::GenerateRequestNo();
	myHandle.AddTask(two);
	three.RequestNo = Task::GenerateRequestNo();
	myHandle.AddTask(three);
	
	cout << "Begin\n";

	Task toDo;
	while (true)
	{
		if (myHandle.GetTask(toDo))
		{
			cout << "funnc = " << toDo.funcno << ", requestno = " << toDo.RequestNo << endl;
		}

		std::this_thread::sleep_for(chrono::microseconds(100));
		Task four;
		four.funcno = 9005;
		four.uType = TASK_REQUEST_COMMON;
		myHandle.AddTask(four);
	}


	system("pause");
}