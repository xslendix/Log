# Header-only logging library

Usage:

```cpp
#include "log.hpp"

int main()
{
	Log::Init();      // Initialize for logging in files with error and exit handling.
	Log::Init(false); // Initialize for logging in files without error and exit handling.

	Log::I("Info test");
	Log::D("Debug test");
	Log::W("Warning test");
	Log::E("Error test");

	return 0;
}
```

