#pragma once

#include "comm_inc.h"

template <typename T1, typename T2>
class Test {
public:
    Test(T1 i, T2 j) : a(i), b(j)
    {
        cout << "模板类" << endl;
    }
private:
    T1 a;
    T2 b;
};

template<>
class Test<int, char> {
public:
    Test(int i, char j) :a(i), b(j) {
        cout << "全特化" << endl;
    }
private:
    int a;
    char b;
};

template<typename T2>
class Test<char, T2> {
public:
    Test(char i, T2 j) :a(i), b(j) {
        cout << "偏特化\n";
    }
private:
    char a;
    T2 b;
};

//模板函数
template<typename T1, typename T2>
void fun(T1 a, T2 b) {
    cout << "模板函数\n";
}
//全特化
template<>
void fun(int, char) {
    cout << "全特化\n";
}

//偏特化代码，错误，无法通过编译
template <typename T2>
void fun(char a, T2 b) {
    cout << "偏特化: " << a << " -- " << b <<endl;
}

void TestTemplate()
{
    Test<double, double> t1(0.1, 0.2);
    Test<int, char> t2(1, 'A');
    Test<char, bool> t3('A', true);

    fun('1', "string");
}