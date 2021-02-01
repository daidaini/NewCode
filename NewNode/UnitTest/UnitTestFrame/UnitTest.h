#ifndef __h_test_case_h__
#define __h_test_case_h__
#include <string>
#include <vector>
#include "TestCommon.h"

using namespace std;
namespace UTest
{
	typedef bool(*TestFunc)(std::string& errorMsg);

	class TestCase
	{
	public:
		TestCase(const std::string& suiteName, const std::string& caseName, TestFunc testFunc);
		~TestCase();

		bool Execute();

		void ReportResult();

	private:
		std::string m_SuiteName;
		std::string m_CaseName;
		bool m_Result;
		std::string m_ResultMsg;
		TestFunc m_TestFunc;
	};

	void AddCase(const std::string& suiteName, const std::string& caseName, TestFunc testFunc);

	int ExecCases();
}




#define ADD_CASE(SUITE_NAME, TEST_FUNC) UTest::AddCase(SUITE_NAME, #TEST_FUNC, TEST_FUNC)


#endif