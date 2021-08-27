# Simple header-only logging library

Usage:

```cpp
#include "log.hpp"

int main()
{
	Log::Init();      // Initialize for logs directory.
	Log::Init(false); // Initialize for logs directory without error and exit handling.

	Log::I("Info test");
	Log::D("Debug test");
	Log::W("Warning test");
	Log::E("Error test");

	return 0;
}
```

