
#include "comm_inc.h"

condition_variable my_cv;
mutex my_mt;

void tFunc()
{
	cout << "This is tFunc\n";
	my_cv.notify_one();
	this_thread::sleep_for(chrono::seconds(2));
}

void tFuncW()
{
	cout << "This is tFuncW\n";
	unique_lock<mutex> lock(my_mt);
	my_cv.wait_for(lock, chrono::seconds(5));

	cout << "I Got it\n";
}

void TestCv()
{
	thread t1(tFunc);
	thread t2(tFuncW);

	t1.join();
	t2.join();
}