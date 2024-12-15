#include <chrono>
#include <ctime>
#include <cstring>
#include <string>

#include "Eris_Log/TimeFormatter.h"

namespace ELog {

TimeFormatter TimeFormatter::s_datetime =			TimeFormatter();
TimeFormatter TimeFormatter::s_date =				TimeFormatter("%d %b %Y");
TimeFormatter TimeFormatter::s_time =				TimeFormatter("%H:%M:%S");
TimeFormatter TimeFormatter::s_file =				TimeFormatter("%Y-%m-%d_%H-%M-%S");
TimeFormatter TimeFormatter::s_programStart =		TimeFormatter("%Y-%m-%d_%H-%M-%S");


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

	strncpy_s(time_format, "%d %b %Y - %H:%M:%S", strlen("%d %b %Y - %H:%M:%S") + 1);

	strftime(str, 64, time_format, &last_tm_time);
}

void TimeFormatter::changeFormat(const char* newFormat) {
	strncpy_s(time_format, newFormat, strlen(newFormat) + 1);
	strftime(str, 64, time_format, &last_tm_time);
}

}