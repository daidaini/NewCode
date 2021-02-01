#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
void printValue(const T& t)
{
	cout << t << ",";
}

/*可变参数模板的使用
*/
template <typename... Args>
void CheckValue(const Args&... args)
{
	initializer_list<int>{(printValue(args), 0)...};
}

/*initialize_list
*/
class Warriors
{
public:
	Warriors(const initializer_list<string>& members)
	{
		for (auto& data : members)
		{
			players.emplace_back(data);
		}
	}

	vector<string> players;

	void print()
	{
		for (auto itm : players)
			std::cout << itm << endl;
	}
};