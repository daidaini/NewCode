#pragma once

#include "comm_inc.h"

class Elem
{
public:
	Elem()
	{
		cout << "Elem()" << endl;
	}

	Elem(const Elem& rhs)
	{
		cout << "Copy Elem()" << endl;
	}

	Elem operator=(const Elem &rhs)
	{
		cout << "Assignment Elem()" << endl;
	}

	int a = 10;
};

/*����queueԪ�ض�ȡʱ��= �Ƿ��п�����Ϊ
*/
void TestQueueRead()
{
	queue<Elem> my_q;
	Elem e1;
	Elem e2;
	Elem e3;
	Elem e4;

	my_q.push(e1);
	my_q.push(e2);
	my_q.push(e3);
	my_q.push(e4);

	Elem get = my_q.back();
	my_q.pop();

	cout << get.a << endl;

}