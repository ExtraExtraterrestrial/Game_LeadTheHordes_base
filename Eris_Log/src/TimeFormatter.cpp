#include <chrono>
#include <ctime>
#include <cstring>
#include <string>
#include <mutex>

#include "Eris_Log/TimeFormatter.h"

namespace ELog {

TimeFormatter TimeFormatter::datetime{};
TimeFormatter TimeFormatter::date{"%d %b %Y"};
TimeFormatter TimeFormatter::time{"%H:%M:%S"};
TimeFormatter TimeFormatter::file{"%Y-%m-%d_%H-%M-%S"};
const TimeFormatter TimeFormatter::programStart{"%Y-%m-%d_%H-%M-%S"};


TimeFormatter::TimeFormatter(const char format_[]) {

	std::time(&last_raw_time);
	localtime_s(&last_tm_time, &last_raw_time);

	strncpy_s(time_format, format_, strlen(format_) + 1);

	strftime(str, 64, format_, &last_tm_time);
}

TimeFormatter::TimeFormatter(std::string &format_) {


	std::time(&last_raw_time);
	localtime_s(&last_tm_time, &last_raw_time);

	strncpy_s(time_format, format_.c_str(), strlen(format_.c_str()) + 1);

	strftime(str, 64, format_.c_str(), &last_tm_time);
}

TimeFormatter::TimeFormatter() {


	std::time(&last_raw_time);
	localtime_s(&last_tm_time, &last_raw_time);

	strncpy_s(time_format, "%H:%M:%S - %d %b %Y", strlen("%H:%M:%S - %d %b %Y") + 1);

	strftime(str, 64, time_format, &last_tm_time);
}

const char *TimeFormatter::getNowStr() {
	std::time(&last_raw_time);
	localtime_s(&last_tm_time, &last_raw_time);
	strftime(str, 64, time_format, &last_tm_time);

	return this->str;
}

void TimeFormatter::update() {
	mutex_update.lock();
	
	std::time(&last_raw_time);
	localtime_s(&last_tm_time, &last_raw_time);
	strftime(str, 64, time_format, &last_tm_time);
	
	mutex_update.unlock();
}

}