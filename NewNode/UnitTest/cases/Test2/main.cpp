#include "Case1.hpp"
#include "Case2.hpp"


int main()
{
	CPtkConfs::GetInstance().ReadConfigs();

	TaskWithTimeControlTest::RegisterCases();
	PtkConfsTest::RegisterCases();

	return UTest::ExecCases();
}
