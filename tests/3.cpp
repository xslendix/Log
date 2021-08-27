#include "log.hpp"

int main()
{
	Log::Init();

	Log::I(1);
	Log::D(true);
	Log::W(0.56);
	Log::E("Sample text");

	return 0;
}

