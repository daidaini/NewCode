#pragma once

#include <chrono>

using namespace std;
using namespace std::chrono;

class CTimeInterval
{
public:
	CTimeInterval()
	{
		m_ShouldSendTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}

	/*
	*@param timeInterval 表示请求可用的间隔时间
	*/
	void SetAvailibleTime(int timeInterval)
	{
		m_ShouldSendTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() + timeInterval;
	}

	bool ShouldSend() const
	{
		return m_ShouldSendTime < duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}

private:
	long long m_ShouldSendTime;
};
