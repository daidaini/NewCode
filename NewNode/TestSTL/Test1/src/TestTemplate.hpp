#pragma once

#include "comm_inc.h"

template <typename T1, typename T2>
class Test {
public:
    Test(T1 i, T2 j) : a(i), b(j)
    {
        cout << "ģ����" << endl;
    }
private:
    T1 a;
    T2 b;
};

template<>
class Test<int, char> {
public:
    Test(int i, char j) :a(i), b(j) {
        cout << "ȫ�ػ�" << endl;
    }
private:
    int a;
    char b;
};

template<typename T2>
class Test<char, T2> {
public:
    Test(char i, T2 j) :a(i), b(j) {
        cout << "ƫ�ػ�\n";
    }
private:
    char a;
    T2 b;
};

//ģ�庯��
template<typename T1, typename T2>
void fun(T1 a, T2 b) {
    cout << "ģ�庯��\n";
}
//ȫ�ػ�
template<>
void fun(int, char) {
    cout << "ȫ�ػ�\n";
}

//ƫ�ػ����룬�����޷�ͨ������
template <typename T2>
void fun(char a, T2 b) {
    cout << "ƫ�ػ�: " << a << " -- " << b <<endl;
}

void TestTemplate()
{
    Test<double, double> t1(0.1, 0.2);
    Test<int, char> t2(1, 'A');
    Test<char, bool> t3('A', true);

    fun('1', "string");
}