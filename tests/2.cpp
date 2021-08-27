#include "log.hpp"

#include <errno.h>

int main()
{
	Log::Init();

	Log::I("Crash test");

	errno = EFAULT;
	throw 0;

	return 0;
}

