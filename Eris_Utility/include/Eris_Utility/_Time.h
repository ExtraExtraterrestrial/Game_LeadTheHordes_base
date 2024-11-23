#pragma once

#include <chrono>
#include <string>

class _Time {
private:
	time_t raw_time;
	tm tm_time;

#	pragma warning( suppress : 4251 )
	std::string str;
	char format[128];
	char buffer[32];

public:
	_Time(const char format_[])
	{
		strcpy_s(format, format_);
		raw_time	= std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		localtime_s(&tm_time, &raw_time);
		strftime(buffer, sizeof(buffer), format, &tm_time);
		str			= buffer;
	}

	_Time() {
		strcpy_s(format, "%d %b %Y - %H:%M:%S");
		raw_time			= std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		localtime_s(&tm_time, &raw_time);
		strftime(buffer, sizeof(buffer), format, &tm_time);
		str					= buffer;
	}

	void now() {
		raw_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		localtime_s(&tm_time, &raw_time);
		strftime(buffer, sizeof(buffer), format, &tm_time);
		str = buffer;
	}


	void changeFormat(char newFormat[]) {

		strcpy_s(format, newFormat);
		strftime(buffer, sizeof(buffer), format, &tm_time);
		str = buffer;
	}


	inline const std::string&	getNowStr()		{ now(); return this->str; };
	inline const std::string&	getStr() const	{ return this->str; }
	inline const time_t&		getRaw() const	{ return this->raw_time; }
	inline const tm&			getTm()	 const	{ return this->tm_time; }

	static _Time s_programStartTime;
	static _Time s_datetime;
	static _Time s_file;
	static _Time s_date;
	static _Time s_time;
};


