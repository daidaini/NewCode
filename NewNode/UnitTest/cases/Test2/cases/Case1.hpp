#pragma once

#include "UnitTest.h"
#include "TaskWithTimeControl.h"


#include "comm_inc.h"

namespace TaskWithTimeControlTest
{
	static CTaskWithTimeControl myHandle = map<int, int>{{9005, 1000}, { 9007, 4000 }};
	bool Case1(std::string& error_msg)
	{
		/*连续添加同一任务，只会在任务队列和延迟队列中获取一次
		*/
		Task one;
		one.funcno = 9005;
		one.uType = TASK_REQUEST_COMMON;
		myHandle.AddTask(one);

		Task two;
		two.funcno = 9005;
		two.uType = TASK_REQUEST_COMMON;
		myHandle.AddTask(two);

		Task three;
		two.funcno = 9005;
		two.uType = TASK_REQUEST_COMMON;
		myHandle.AddTask(two);

		Task toGet;
		ASSERT_TRUE(myHandle.GetTask(toGet));
		ASSERT_FALSE(myHandle.GetTask(toGet));
		ASSERT_FALSE(myHandle.GetTask(toGet));

		return true;
	}

	bool Case2(std::string& error_msg)
	{
		Task one;
		one.funcno = 9006;
		one.uType = TASK_REQUEST_COMMON;
		myHandle.AddTask(one);

		Task two;
		two.funcno = 9006;
		two.uType = TASK_REQUEST_COMMON;
		myHandle.AddTask(two);

		Task three;
		two.funcno = 9006;
		two.uType = TASK_REQUEST_COMMON;
		myHandle.AddTask(two);

		Task toGet;
		ASSERT_TRUE(myHandle.GetTask(toGet));
		ASSERT_TRUE(myHandle.GetTask(toGet));
		ASSERT_TRUE(myHandle.GetTask(toGet));

		return true;
	}

	bool Case3(std::string& error_msg)
	{
		Task one;
		one.funcno = 9005;
		one.uType = TASK_REQUEST_COMMON;
		myHandle.AddTask(one);

		Task toGet;
		ASSERT_TRUE(myHandle.GetTask(toGet));


		Task two;
		two.funcno = 9005;
		two.uType = TASK_REQUEST_COMMON;
		myHandle.AddTask(two);
		ASSERT_FALSE(myHandle.GetTask(toGet));
		this_thread::sleep_for(milliseconds(2400));
		ASSERT_TRUE(myHandle.GetTask(toGet));

		return true;
	}

	void RegisterCases()
	{
		ADD_CASE("TaskWithTimeControlTest", TaskWithTimeControlTest::Case2);
	}
}
