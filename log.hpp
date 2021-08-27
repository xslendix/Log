#pragma once

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>

#ifndef __has_include
  static_assert(false, "__has_include not supported");
#else
#if __cplusplus >= 201703L && __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#elif __has_include(<boost/filesystem.hpp>)
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#endif
#endif

#include <string>
#include <stdio.h>
#include <time.h>

// https://stackoverflow.com/a/10467633/9438759
const std::string _current_date_time() {

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%T", &tstruct);

    return buf;

}

const std::string _get_log_filename() {

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "logs/log-%Y-%m-%d.%H-%M-%S.txt", &tstruct);

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

	std::ofstream _current_file;
	std::string _filename;

	void SetLevel(const Level level)
	{
		_current_level = level;
	}

	template<typename T>
	void Print(const Level level, T data)
	{
		std::string prefix = "";

		switch (level) {
			case INFO:
				prefix = "INFO:  ";
				break;
			case DEBUG:
				prefix = "DEBUG: ";
				break;
			case WARN:
				prefix = "WARN:  ";
				break;
			case ERROR:
				prefix = "ERROR: ";
				break;
		}

		_current_file << '[' << _current_date_time() << "] " << prefix << data << '\n';

		if (level < _current_level)
			return;

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
	
		std::cerr << '[' << _current_date_time() << "] " << prefix << data << '\n';
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

	void _exiting()
	{
		I("Safely exiting...");

		_current_file.close();
	}

	void _terminate()
	{
		std::stringstream ss;

		ss << "Exception detected: " << std::strerror(errno);

		E(ss.str());

		_current_file.close();

		abort();
	}

	void Init(bool failsafe=true)
	{
		if (failsafe) {
			std::set_terminate(_terminate);
			std::atexit(_exiting);
		}

		if (!fs::is_directory("logs") || !fs::exists("logs"))
			fs::create_directory("logs");

		_filename = _get_log_filename();

		if (!fs::exists(_filename))
			_current_file = std::ofstream(_filename);
	}

}

