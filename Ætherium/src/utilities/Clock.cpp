#include "Clock.h"

time_t Clock::now = time(0);

std::string Clock::CreateTimeStamp() {
	now = time(0);
	tm ltm = {};
	localtime_s(&ltm, &now);
	std::stringstream ss;
	ss << ltm.tm_year << "/" << ltm.tm_mon << "/" << ltm.tm_mday << " " << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << std::endl;
	return ss.str();
}
std::wstring Clock::CreateTimeStampW() {
	now = time(0);
	tm ltm = {};
	localtime_s(&ltm, &now); // fill local time
	bool is_pm = false;
	std::wstringstream ss;

	if (ltm.tm_hour > 12) {
		ltm.tm_hour -= 12;
		is_pm = true;
	}

	ss << ltm.tm_mon << L"/" << ltm.tm_mday << L"/" << 1900 + ltm.tm_year << L" " <<
		ltm.tm_hour << L":" << ltm.tm_min << L":" << ltm.tm_sec << (is_pm ? L" PM" : L" AM");
	return ss.str();
}