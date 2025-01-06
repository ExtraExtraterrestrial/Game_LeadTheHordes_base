#include <sstream>
#include <string_view>

#include <fstream>
#include <iostream>

#include "Eris_Log/TimeFormatter.h"
#include "Eris_Log/Log.h"



namespace ELog {

Log Log::instance{};

Log& Log::Get() {
	return instance;
}

Log::Log(int threatLevel, int verboseLevel) 
	: showThreatLevel((ThreatLevels)threatLevel)
	, verboseLevel((VerboseLevels)verboseLevel)
	, commandBuffer("") {
	
#	ifdef OVERWRITE_STL_SYNC
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
#	endif


	bodyLen = 90;
	std::fill(line, line + 120, '_');

	#ifndef LOG_DO_NOT_AUTOSTART
		this->startup();
	#endif
}

Log::~Log() {
	info(__FUNCTION__, __LOG_FILENAME__, __LINE__, "Session ended");
	logFile.close();
}


void Log::startup(std::string_view filePrefix) {

	std::string filePath = "logs";
	filePath += DIR_DELIMITER;
	filePath += TimeFormatter::programStart.getStr();
	filePath += "_";
	filePath += LOG_DEBUG_CHAR;
	filePath += DIR_DELIMITER;
	filePath += filePrefix;
	filePath += TimeFormatter::programStart.getStr();
	filePath += "_";
	filePath += LOG_DEBUG_CHAR;
	filePath += ".log";

	strcpy_s(this->logFilePath, filePath.c_str());
	

	commandBuffer  = "mkdir logs";
	commandBuffer += DIR_DELIMITER;
	commandBuffer += TimeFormatter::programStart.getStr();
	commandBuffer += "_";
	commandBuffer += LOG_DEBUG_CHAR;
	commandBuffer += NULL_FILE_REDIRECT;

	system(commandBuffer.c_str());
	commandBuffer = "";


	std::cout << std::boolalpha << std::left;
	std::cout << (LOG_DEBUG_CHAR == "D" ? "\x1B[35m[DEBUG]\033[0m" : "\x1B[35m[RELEASE]\033[0m") << std::endl;
	
	#if defined(_MSC_FULL_VER)
		std::cout << std::setw(36) << "\x1B[35m[VS STUDIO VERSION]\033[0m" << _MSC_FULL_VER << std::endl;
		std::cout << std::setw(36) << "\x1B[35m[C++ VERSION]\033[0m" << _MSVC_LANG << std::endl << std::endl;
	#elif defined(__GNUG__)
		std::cout << std::setw(36) << "\x1B[35m[GCC VERSION]\033[0m" << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;
		std::cout << std::setw(36) << "\x1B[35m[C++ VERSION]\033[0m" << __cplusplus << std::endl << std::endl;
	#else
		std::cout << std::setw(36) << "\x1B[35m[UNKNOWN COMPILATOR]\033[0m" << std::endl;
	#endif


	std::cout << std::setw(36) << "\x1B[35m[START TIME]\033[0m" << TimeFormatter::datetime.getNowStr() << std::endl;
	std::cout << "\x1B[35m" << line << "\033[0m\n" << std::endl;


	logFile.open(logFilePath);
	if (logFile.is_open()) {
		logFile << std::boolalpha << std::left;
		logFile << (LOG_DEBUG_CHAR == "D" ? "[DEBUG]" : "[RELEASE]") << std::endl;
	
		#if defined(_MSC_FULL_VER)
			logFile << std::setw(36) << "[VS STUDIO VERSION]" << _MSC_FULL_VER << std::endl;
			logFile << std::setw(36) << "[C++ VERSION]" << _MSVC_LANG << std::endl << std::endl;
		#elif defined(__GNUG__)
			logFile << std::setw(36) << "\x1B[35m[GCC VERSION]\033[0m" << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;
			logFile << std::setw(36) << "\x1B[35m[C++ VERSION]\033[0m" << __cplusplus << std::endl << std::endl;
		#else
			logFile << std::setw(36) << "\x1B[35m[UNKNOWN COMPILATOR]\033[0m" << std::endl;
		#endif

		logFile << std::setw(36) << "[START TIME]" << TimeFormatter::datetime.getNowStr() << std::endl;
		logFile << line << std::endl;

	} else {

		std::cout << std::left 
			<< "\x1B[31m[" << TimeFormatter::time.getNowStr() << "]  " << "(ERROR)\n"
			<< "FAILED TO OPEN LOG FILE" << "\033[0m\n" << logFilePath << "\n";

		commandBuffer  = "pause ";
		commandBuffer += NULL_FILE_REDIRECT;

		system(commandBuffer.c_str());
		commandBuffer = "";
	}
}

}