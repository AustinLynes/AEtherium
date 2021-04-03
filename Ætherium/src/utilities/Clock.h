#pragma once
#include <string>
#include <sstream>
#include <time.h>

class Clock {
public:
	static std::string CreateTimeStamp();
	static std::wstring CreateTimeStampW();

	static time_t now; // time since epoch
};