#pragma once

namespace ELog {

class TimeFormatter {
public:
	TimeFormatter(const char format_[]);
	TimeFormatter(std::string &format_);
	TimeFormatter();


	inline const char*			getStr() const	{ return this->str; }
	inline const time_t&		getRaw() const	{ return this->last_raw_time; }
	inline const tm&			getTm()	 const	{ return this->last_tm_time; }

	const char *getNowStr();

	void update();

	void changeFormat(const char* newFormat);

	
private:
	time_t last_raw_time;
	tm last_tm_time;

	char str[64];
	char time_format[32];


public:

	static TimeFormatter datetime;
	static TimeFormatter date;
	static TimeFormatter time;
	static TimeFormatter file;
	static const TimeFormatter programStart;

};


}