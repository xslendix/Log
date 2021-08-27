#include "log.hpp"

int main()
{
	Log::I("Info test");
	Log::D("Debug test");
	Log::W("Warning test");
	Log::E("Error test");

	return 0;
}

