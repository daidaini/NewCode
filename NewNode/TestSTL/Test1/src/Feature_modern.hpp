#pragma once

#include "comm_inc.h"


/*关于final 在虚函数中的使用
*/
struct Base
{
	virtual void fool(int x)
	{

	}
};

struct SubBase : public Base
{
	virtual void fool(int x) final
	{

	}
};

/*
struct SSubBase : public SubBase
{
	virtual void fool(int x)
	{

	}
};
*/



/*initializer_list
*/
class MagicFoo
{
	map<int, string> m_confs;
public:
	MagicFoo(std::initializer_list<pair<int, string>> pairs)
	{
		for (const auto& mem : pairs)
		{
			m_confs.insert(make_pair(mem.first, mem.second));
		}
	}

	void print()
	{
		for (auto& [key, value] : m_confs)
		{
			cout << key << " = " << value << endl;
		}
	}

};

void test_magicfool()
{
	MagicFoo my_fool = { {1, "first"} , {2, "second"} };

	my_fool.print();
}


/*测试左值和右值传参使用
*/
void reference(string& v)
{
	cout << "左值引用" << endl;
}

void reference(string&& v)
{
	cout << "右值引用" << endl;
}

template<typename T>
void pass(T&& v)
{
	cout << "普通传参: ";
	reference(v);
	cout << "std::move传参: ";
	reference(std::move(v));
	cout << "std::forward传参: ";
	reference(std::forward<T>(v));
	cout << "static_cast<T&&>传参: ";
	reference(static_cast<T&&>(v));
}

void test_pass_value()
{
	cout << "测试传递右值：" << endl;
	pass("This is tesing");

	cout << "----------------------------\n";

	cout << "测试传递左值：" << endl;
	string data = "This is testing";
	pass(data);
}