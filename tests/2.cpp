#include "log.hpp"

#include <errno.h>

int main()
{
	Log::Init();

	Log::I("Crash test");

	throw ECONNABORTED;

	return 0;
}

