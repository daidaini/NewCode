#pragma once

#include "Singleton.h"

#include <map>

class CPtkConfs : public Singleton<CPtkConfs>
{
	friend class Singleton<CPtkConfs>;
public:
	void ReadConfigs();

	std::map<int, int> GetQueryLimitConfig();

private:
	void ReadQueryLimits();

private:
	std::map<int, int> m_QueryLimits;
};