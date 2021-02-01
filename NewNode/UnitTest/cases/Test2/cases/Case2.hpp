#pragma once

#include "UnitTest.h"
#include "PtkConfs.h"

namespace PtkConfsTest
{
	bool Case1(std::string& error_msg)
	{
		std::map<int, int> confs = CPtkConfs::GetInstance().GetQueryLimitConfig();

		ASSERT_EQUAL(confs.size(), 2);
		ASSERT_EQUAL(confs[9005], 3000);

		return true;
	}

	void RegisterCases()
	{
		

		ADD_CASE("PtkConfsTest", Case1);
	}
}