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

//template<typename ... T>
//auto average(T ... t)
//{
//	return (t + ...) / sizeof...(t); //这个sizeof的用法？
//}
//
//void test_average()
//{
//	cout << average(1.0, 2, 3, 4, 5, 6,7,8,9,10) << endl;
//}


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


/*structured binding
*/
template <typename Key, typename Value, typename F>
void update(std::map<Key, Value>& m, F fool)
{
	for (auto& [key, value] : m)
		value = fool(key);

	//for (auto& elem : m)
	//	elem.second = fool(elem.first);
}

void test_update()
{
	map<string, long long int> m{
		{"a",1},
		{"b",2},
		{"c",3}
	};
	update(m, [](string key) {
		return hash<string>{}(key);
		});

	for (auto&& [key, value] : m)
		cout << key << " : " << value << endl;
}


void StructedBindTest()
{
	tuple my_tup = { 1,3.0,"five" };

	auto &[f, s, t] = my_tup;

	t = "Friday";

	cout << f << " " << s << " " << t << "\n";
}

struct Point {
	int x;
	int y;
};

Point func()
{
	return { 1,2 };
}

void StructedBindTest_1()
{
	int arr[3] = { 1,3,5 };
	auto [a, b, c] = arr;
	cout << a << "," << c << "," << b << "\n";

	const auto [x, y] = func();
	cout << x << " " << y << endl;
}

void CharconvTest()
{
	string str{ "123456798" };
	int value = 0;

	const auto res = from_chars(str.data(), str.data() + 11, value);
	if (res.ec == std::errc())
	{ 
		cout << value << ",distance " << res.ptr - str.data() << endl;
	}
	else if (res.ec == std::errc::invalid_argument)
	{
		cout << "invalid\n";
	}

	str = std::string("xxxxxxxx");
	const int v = 1234;
	auto res2 = std::to_chars(str.data(), str.data() + str.size(), v);
	cout << str << ", filled " << res2.ptr - str.data() << " characters \n";
	// 1234xxxx, filled 4 characters
 }

void VariantTest() {
	variant <int, string> var("hello");

	variant <int, string> var_2(2021);

	var = 20210301;
	var_2 = "world";

	cout << std::get<int>(var) << endl;
	
	cout << std::get<1>(var_2) << endl;
}


void ApplyTest()
{
	auto add_lambda = [](auto first, auto second, auto third) {return first + second + third; };

	cout << std::apply(add_lambda, std::make_tuple(10.3, 11, 12.45)) <<endl;

	cout << std::apply(add_lambda, std::make_tuple(10, 11, 12)) << endl;
}

struct Foo {
	Foo(int first, float second, string third) {
		cout << first << ", " << second << ", " << third << endl;
	}
};

constexpr void MakeFromTupleTest() noexcept
{
	auto tuple = make_tuple(42, 3.14f, "Saturday");
	make_from_tuple<Foo>(std::move(tuple));
}