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
	*@param timeInterval ��ʾ������õļ��ʱ��
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
