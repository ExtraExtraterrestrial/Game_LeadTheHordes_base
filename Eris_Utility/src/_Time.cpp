#include <chrono>
#include <ctime>
#include <cstring>

#include "Eris_Utility/_Time.h"


_Time _Time::s_datetime =			_Time();
_Time _Time::s_date =				_Time("%d %b %Y");
_Time _Time::s_time =				_Time("%H:%M:%S");
_Time _Time::s_file =				_Time("%Y-%m-%d_%H-%M-%S");
_Time _Time::s_programStartTime =	_Time("%Y-%m-%d_%H-%M-%S");


_Time::_Time(const char format_[]) {

	std::time(&last_raw_time);
	 localtime_s(&last_tm_time, &last_raw_time);

	 strncpy_s(time_format, format_, strlen(format_) + 1);

	 strftime(str, 64, format_, &last_tm_time);
}

_Time::_Time(std::string &format_) {

	std::time(&last_raw_time);
	localtime_s(&last_tm_time, &last_raw_time);

	strncpy_s(time_format, format_.c_str(), strlen(format_.c_str()) + 1);

	strftime(str, 64, format_.c_str(), &last_tm_time);
}

_Time::_Time() {

	std::time(&last_raw_time);
	localtime_s(&last_tm_time, &last_raw_time);

	strncpy_s(time_format, "%d %b %Y - %H:%M:%S", strlen("%d %b %Y - %H:%M:%S") + 1);

	strftime(str, 64, time_format, &last_tm_time);
}

void _Time::changeFormat(const char* newFormat)
{
	strncpy_s(time_format, newFormat, strlen(newFormat) + 1);
	strftime(str, 64, time_format, &last_tm_time);
}
