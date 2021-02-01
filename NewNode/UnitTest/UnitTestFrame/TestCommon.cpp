#include "TestCommon.h"
#include <exception>

char message_buffer[4096];


void throw_exception(const char* msg)
{
	std::exception e(msg);
	throw e;
}
