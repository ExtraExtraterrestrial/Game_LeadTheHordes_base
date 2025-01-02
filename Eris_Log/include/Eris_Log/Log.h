#pragma once

#include <cstdarg>
#include <iomanip>
#include <cstring>


// #include "../src/Log.tpp" at the bottom
// #define LOG_DO_NOT_AUTOSTART use this header if you want to change filename

namespace ELog {

#if defined(__linux__) || defined(LINUX)
	#define				DIR_DELIMITER	 	"/"
	#define				NULL_FILE_REDIRECT  " 2> /dev/null"
#elif defined(_WIN32)
	#define				DIR_DELIMITER	 	"\\"
	#define				NULL_FILE_REDIRECT  " 2> nul"
#else
	#error				_WIN32, __linux__ and LINUX undefined - system not recognized
#endif // defined(__linux__) or defined(LINUX)

//<3// thanks to https://stackoverflow.com/a/8488201/16614732 for the line below
#define __LOG_FILENAME__ (std::strrchr(__FILE__, DIR_DELIMITER[0]) ? std::strrchr(__FILE__, DIR_DELIMITER[0]) + 1 : __FILE__)

#if defined(_DEBUG) || (!defined(NDEBUG) && defined(__GNUC__))
	#define			LOG_DEBUG_CHAR			"D"		// D if debug, R if release
#else
	#define			LOG_DEBUG_CHAR			"R"		// D if debug, R if release
#endif



class Log {
public:
	static Log& Get();

	Log(const Log&) = delete;
	~Log();
private:
	enum ThreatLevels : int {		// Warning level to log
		ErrorLvl, WarningLvl, InfoLvl
	}; ThreatLevels showThreatLevel;

	enum VerboseLevels : int {		// Head, or head and body
		NoVerbose, LowVerbose, FullVerbose
	}; VerboseLevels verboseLevel;

	char logFilePath[128];
	std::string commandBuffer;

	std::ofstream logFile;

	short bodyLen;			// specifies how many character per line (after 3 tabs)
	char line[128];			// remember to change it each time

	Log(int threatLevel = 2, int verboseLevel = 2);
	static Log instance;

public:
	void startup(std::string_view filePrefix = "EUtil__");

	inline void setLevel(int threatLevel, int verboseLevel) {
		this->showThreatLevel = (ThreatLevels)threatLevel;
		this->verboseLevel = (VerboseLevels)verboseLevel;
	}
	inline void setThreatLevel(int threatLevel) { this->showThreatLevel = (ThreatLevels)threatLevel; }
	inline void setVerboseLevel(int verbLevel) { this->showThreatLevel = (ThreatLevels)verbLevel; }

	// definitions in Log.tpp since they're templates
	template<typename Func = std::string_view, typename File = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void info(Func func_name, File file_name, int line, H head, B body, ...);
	template<typename Func = std::string_view, typename File = std::string_view, typename H = std::string_view>
	void info(Func func_name, File file_name, int line, H head);


	template<typename Func = std::string_view, typename File = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void success(Func func_name, File file_name, int line, H head, B body, ...);
	template<typename Func = std::string_view, typename File = std::string_view, typename H = std::string_view>
	void success(Func func_name, File file_name, int line, H head);


	template<typename Func = std::string_view, typename File = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void warn(Func func_name, File file_name, int line, H head, B body, ...);
	template<typename Func = std::string_view, typename File = std::string_view, typename H = std::string_view>
	void warn(Func func_name, File file_name, int line, H head);


	template<typename Func = std::string_view, typename File = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void error(Func func_name, File file_name, int line, H head, B body, ...);
	template<typename Func = std::string_view, typename File = std::string_view, typename H = std::string_view>
	void error(Func func_name, File file_name, int line, H head);

	template<typename Func = std::string_view, typename File = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void assert_(Func func_name, File file_name, int line, bool condition, H head, B body, ...);
	template<typename Func = std::string_view, typename File = std::string_view, typename H = std::string_view>
	void assert_(Func func_name, File file_name, int line, bool condition, H head);
};


}

#include "../src/Log.tpp"

// copy and paste into your code!
// macros with _R suffix will work in release
#ifdef ERIS_UTILITY_PREMADE_MACROS

// ErisUtility _Time
#define			T_PROGRAM_START_TIME			_Time::s_programStartTime.getStr()		// returns string&, safe for file naming
#define			T_FILE_STR						_Time::s_file.getNowStr()				// returns string&, safe for file naming
#define			T_DATE_STR						_Time::s_date.getNowStr()				// returns string& with current date
#define			T_DATE_CHG_FORMAT(f)			_Time::s_date.changeFormat(f)			// changes date format
#define			T_TIME_STR						_Time::s_time.getNowStr()				// returns string& with current time
#define			T_TIME_CHG_FORMAT(f)			_Time::s_time.changeFormat(f)			// changes format of time
#define			T_DATETIME_STR					_Time::s_datetime.getNowStr()			// returns string& with current datetime
#define			T_DATETIMET_CHG_FORMAT(f)		_Time::s_datetime.changeFormat(f)		// changes format of datetime

// ErisUtility Log
#define			LOG_SETLEVEL(threat, verb)		Log::Get().setLevel(threat, verb)
#define			LOG_INFO(...)					Log::Get().info(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_WARN(...)					Log::Get().warn(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_SUCC(...)					Log::Get().success(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)	// head, body and args to format body in c-style
#define			LOG_ERR(...)					Log::Get().error(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style

#endif //ERIS_UTILITY_PREMADE_MACROS
