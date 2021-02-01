#pragma once

#include "comm_inc.h"



void TestAllOf()
{
	//map<int, int> my_map;
	vector<int> my_vec;

	for (size_t i = 0; i < 100; i++)
	{
		my_vec.push_back(i + 10);
	}

	for_each(my_vec.begin(), my_vec.end(), [](int elem)
	{
		cout << elem << " ";
	});

	cout << endl;

	int toComp = 0;

	while (true)
	{
		cout << "ÊäÈë¼ì²âÊý×Ö:\n";
		cin >> toComp;

		if (toComp == 0)
			break;

		cout << any_of(my_vec.begin(), my_vec.end(), [toComp](int elem){
			return elem == toComp;
		}) << endl;
	}
	
}