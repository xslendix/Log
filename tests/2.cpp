#include "log.hpp"

#include <errno.h>

int main()
{
	Log::Init();

	Log::I("Crash test");

	throw std::system_error(EFAULT, std::generic_category());

	return 0;
}

