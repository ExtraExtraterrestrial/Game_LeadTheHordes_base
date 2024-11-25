#pragma once

class _Time {
public:
	_Time(const char format_[]);
	_Time(std::string &format_);
	_Time();


	inline const char*			getStr() const	{ return this->str; }
	inline const time_t&		getRaw() const	{ return this->last_raw_time; }
	inline const tm&			getTm()	 const	{ return this->last_tm_time; }

	inline const char* getNowStr() {
		std::time(&last_raw_time);
		localtime_s(&last_tm_time, &last_raw_time);
		strftime(str, 64, time_format, &last_tm_time);

		return this->str;
	}

	inline void update() {
		std::time(&last_raw_time);
		localtime_s(&last_tm_time, &last_raw_time);
		strftime(str, 64, time_format, &last_tm_time);
	}

	void changeFormat(const char* newFormat);

	
private:
	time_t last_raw_time;
	tm last_tm_time;

	char str[64];
	char time_format[32];

public:
	static _Time s_datetime;
	static _Time s_date;
	static _Time s_time;
	static _Time s_file;
	static _Time s_programStartTime;
};


