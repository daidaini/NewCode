#pragma once 

#include "comm_inc.h"

using namespace std::chrono;

class MyTimer
{
public:
	MyTimer() : m_begin(high_resolution_clock::now())
	{
	}

	void Reset()
	{
		m_begin = high_resolution_clock::now();
	}

	//ƒ¨»œ ‰≥ˆ∫¡√Î
	int64_t elapsed() const
	{
		return duration_cast<milliseconds>(high_resolution_clock::now() - m_begin).count();
	}

	int64_t elapsed_nano() const
	{
		return duration_cast<nanoseconds>(high_resolution_clock::now() - m_begin).count();
	}

	int64_t elapsed_seconds() const
	{
		return duration_cast<seconds>(high_resolution_clock::now() - m_begin).count();
	}

private:
	time_point<high_resolution_clock> m_begin;
};

