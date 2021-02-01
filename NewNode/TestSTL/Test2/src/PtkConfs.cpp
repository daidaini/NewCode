#include "PtkConfs.h"
#include "json\json.h"
#include "Utility.h"

void CPtkConfs::ReadConfigs()
{
	ReadQueryLimits();
}

void CPtkConfs::ReadQueryLimits()
{
	const std::string filename = "./TradeMidWare/QueryLimit.json";

	std::string contents = Utility::ReadContentsFromFile(filename);
	if (contents.empty())
	{
		return;
	}

	Json::Reader jReader;
	Json::Value jVal;

	if (!jReader.parse(contents, jVal))
	{
		return;
	}

	try
	{
		if (!jVal.isArray())
		{
			return;
		}

		for (int i = 0; i < jVal.size(); ++i)
		{
			m_QueryLimits.emplace(jVal[i]["功能号"].asInt(), jVal[i]["最小时间间隔"].asInt());
		}
	}
	catch (Json::LogicError e)
	{
	}
}

std::map<int, int> CPtkConfs::GetQueryLimitConfig()
{
	return m_QueryLimits;
}