#include "UnitTest.h"
#include <iostream>

using namespace std;

namespace UTest
{

	std::vector<TestCase*> g_TestCases;

	TestCase::TestCase(const std::string& suiteName, const std::string& caseName, TestFunc testFunc)
	{
		m_SuiteName = suiteName;
		m_CaseName = caseName;
		m_TestFunc = testFunc;
	}

	TestCase::~TestCase()
	{
	}

	bool TestCase::Execute()
	{
		cout << "ExecuteCase:[" << m_SuiteName << "]\t\t[" << m_CaseName << "]";

		try
		{
			m_Result = (*m_TestFunc)(m_ResultMsg);
		}
		catch (exception e)
		{
			m_Result = false;
			m_ResultMsg = e.what();
		}

		if (m_Result)
		{
			cout << "\t[pass]" << endl;
		}
		else
		{
			cout << "\t[fail]" << endl;
		}


		return m_Result;
	}

	void TestCase::ReportResult()
	{
		cout << endl;
		cout << "TestSuite:\t" << m_SuiteName << endl;
		cout << "TestCase:\t" << m_CaseName << endl;
		cout << "TestResult:\t " << (m_Result ? "Success" : "Fail") << endl;
		cout << "ResultMessage:\t" << m_ResultMsg << endl << endl;
	}

	void AddCase(const std::string& suite_name, const std::string& case_name, TestFunc test_func)
	{
		g_TestCases.push_back(new TestCase(suite_name, case_name, test_func));
	}

	int ExecCases()
	{
		int passed_count = 0;
		int failed_count = 0;
		cout << endl << "-------------------Execute Cases---------------------------------------------------" << endl;
		for (auto it = g_TestCases.begin(); it != g_TestCases.end(); it++)
		{
			if ((*it)->Execute())
			{
				passed_count++;
			}
			else
			{
				failed_count++;
			}
		}

		cout << endl << "-------------------Report Result------------------------------------------------" << endl;
		for (auto it = g_TestCases.begin(); it != g_TestCases.end(); it++)
		{
			(*it)->ReportResult();
		}

		cout << "Execute " << g_TestCases.size() << " cases, " << passed_count << " passed, " << failed_count << " failed." << endl;

		system("pause");
		return failed_count;
	}
}