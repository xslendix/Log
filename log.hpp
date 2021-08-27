#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>

// https://stackoverflow.com/a/10467633/9438759
const std::string _current_date_time() {

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "[%Y-%m-%d %T]", &tstruct);

    return buf;

}

namespace Log {

	enum Level {
		INFO,
		DEBUG,
		WARN,
		ERROR
	};

	auto _current_level = INFO;

	void SetLevel(const Level level)
	{
		_current_level = level;
	}

	template<typename T>
	void Print(const Level level, T data)
	{
		if (level < _current_level)
			return;

		std::string prefix = "";

		switch (level) {
			case INFO:
				prefix = "\33[44m INFO  \33[0m ";
				break;
			case DEBUG:
				prefix = "\33[45m DEBUG \33[0m ";
				break;
			case WARN:
				prefix = "\33[43m WARN  \33[0m ";
				break;
			case ERROR:
				prefix = "\33[41m ERROR \33[0m ";
				break;
		}
	
		std::cout << _current_date_time() << " " << prefix << data << std::endl;
	}

	template<typename T>
	void I(T data)
	{
		Print(INFO, data);
	}

	template<typename T>
	void D(T data)
	{
		Print(DEBUG, data);
	}

	template<typename T>
	void W(T data)
	{
		Print(WARN, data);
	}

	template<typename T>
	void E(T data)
	{
		Print(ERROR, data);
	}
}

