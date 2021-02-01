#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <assert.h>
#include <string>
#include <vector>

class Utility
{
public:


	template<class T>
	static char EnumToChar(T t);

	template<class T>
	static int EnumToInt(T t);

	template<class T>
	static T CharToEnum(char c);

	template<class T>
	static T IntToEnum(int i);



	static std::vector<std::string> ReadLinesFromFile(const std::string filename);

	static std::string ReadContentsFromFile(const std::string filename);
};

template<class T>
char Utility::EnumToChar(T t)
{
	static_assert(sizeof(t) == sizeof(char), "convert is invalid");

	return static_cast<char>(t);
}

template<class T>
int Utility::EnumToInt(T t)
{
	static_assert(sizeof(t) == sizeof(int), "convert is invalid");

	return static_cast<int>(t);
}

template<class T>
T Utility::CharToEnum(char c)
{
	static_assert(sizeof(T) == 1, "convert is invalid");
	return static_cast<T>(c);
}

template<class T>
T Utility::IntToEnum(int i)
{
	static_assert(sizeof(T) == sizeof(int), "convert is invalid");
	return static_cast<T>(i);
}




#endif
