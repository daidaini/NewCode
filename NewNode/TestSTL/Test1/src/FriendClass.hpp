#include <string>
#include <iostream>

using namespace std;

class A
{
	friend class AFriend;
public:
	void print()
	{
		cout << txt << endl;
	}
private:
	std::string txt = "hello";
};

class AFriend
{
public:
	void ModifyStr(const std::string toModify, A &src)
	{
		src.txt = toModify;
		cout << src.txt << endl;
	}
};

void TestFriend()
{
	AFriend f;
	A s;
	f.ModifyStr("not hello", s);

	s.print();
}