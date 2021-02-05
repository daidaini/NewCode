#pragma once

#include "comm_inc.h"

struct TradePushData
{
	TradePushData()
	{
		memset(this, 0, sizeof(*this));
	}
	char ExchangeID[8];
	char ContractID[16];
	char TradeID[32];
	char TradePrice[16];
	char OrderID[16];
	int Volume;
	char TradeSysID[32];
	char Time[16];
	char Date[12];
	char CoverFlag;
	char CoverFlagName[16];
	char BSType;
	char BSTypeName[8];
	char OCType;
	char OCTypeName[16];
	char HedgeFlag;
	char ContractType;
	char ContractName[32];
	char ExtraMsg[128];
};


/*fold expression
*/

template<typename ... T>
auto sum(T ... t) {
	return (t + ...);
}

void TestSum()
{
	std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}

void print_out()
{
	cout << endl;
}

/*variadic templates
*/
template <typename Head, typename... T>
void print_out(Head h, T... data)
{
	cout << h << " , ";
	print_out(data...);
}

void test_print_out()
{
	TradePushData data;

	data.BSType = '1';

	strcpy_s(data.BSTypeName, sizeof(data.BSTypeName), "卖");
	strcpy_s(data.ContractID, sizeof(data.ContractID), "600000");
	data.Volume = 1000;

	print_out(data.BSType, data.BSTypeName, data.ContractID, data.Volume);
}

/*if/switch 变量声明强化
*/
void test_if_assign()
{
	vector<int> vec{ 1,2,3,4,6 };

	if (const auto it = std::find(vec.begin(), vec.end(), 3); 
		it != vec.end())
	{
		cout << *it << endl;
	}
}

void test_switch_assign()
{
	vector<int> vec{ 1,2,3,4,6 };

	switch (auto it = vec[1]; it)
	{
	case 1:
		cout << "first\n";
		break;
	case 2:
		cout << "second\n";
		break;
	default:
		break;
	}
}

/*结构化绑定，简化tuple的使用
*/
tuple<int, double, string> get_results()
{
	return make_tuple(100, 3.1415926, "I am waiting for the reuslts");
}

void test_get_tuple_return()
{
	auto [one, two, three] = get_results();

	cout << one << endl;
	cout << two << endl;  //double 的精度 只有5位？
	cout << three << endl;
}

/*if constexpr
*/
template<typename T>
auto  print_type_info(const T& t)
{
	if constexpr(std::is_integral<T>::value)
	{
		return t + 1;
	}
	else if (std::is_floating_point<T>::value)
	{
		return t + 3.14;
	}
	else
		return t ;
}

