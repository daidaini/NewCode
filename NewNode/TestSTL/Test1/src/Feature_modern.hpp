#pragma once

#include "comm_inc.h"


/*����final ���麯���е�ʹ��
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


/*������ֵ����ֵ����ʹ��
*/
void reference(string& v)
{
	cout << "��ֵ����" << endl;
}

void reference(string&& v)
{
	cout << "��ֵ����" << endl;
}

template<typename T>
void pass(T&& v)
{
	cout << "��ͨ����: ";
	reference(v);
	cout << "std::move����: ";
	reference(std::move(v));
	cout << "std::forward����: ";
	reference(std::forward<T>(v));
	cout << "static_cast<T&&>����: ";
	reference(static_cast<T&&>(v));
}

void test_pass_value()
{
	cout << "���Դ�����ֵ��" << endl;
	pass("This is tesing");

	cout << "----------------------------\n";

	cout << "���Դ�����ֵ��" << endl;
	string data = "This is testing";
	pass(data);
}