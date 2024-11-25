#include <sstream>
#include <string_view>

#include <fstream>
#include <iostream>
#include <cstring>

#include "Eris_Utility/Log.h"

Log Log::instance{};

Log& Log::Get() {
	return instance;
}

void Log::startup() {

	strcpy_s(commandBuffer, "mkdir logs");
	strcat_s(commandBuffer, &DIR_DELIMITER);
	strcat_s(commandBuffer, _Time::s_programStartTime.getStr());
	strcat_s(commandBuffer, " ");
	strcat_s(commandBuffer, NULL_FILE_REDIRECT);
	
	system(commandBuffer);
	memset(commandBuffer, 0, sizeof(commandBuffer));


	logFile.open(logFilePath);

	std::cout << std::boolalpha << std::left;
	std::cout << (LOG_DEBUG_CHAR == 'D' ? "\x1B[35m[DEBUG]\033[0m" : "\x1B[35m[RELEASE]\033[0m") << std::endl;
#ifdef _MSC_FULL_VER
	std::cout << std::setw(36) << "\x1B[35m[VS STUDIO VERSION]\033[0m" << _MSC_FULL_VER << " (1916: Visual Studio 17)" << std::endl;
#endif
#ifdef _MSVC_LANG
	std::cout << std::setw(36) << "\x1B[35m[C++ VERSION]\033[0m" << _MSVC_LANG << std::endl;
#endif
	std::cout << std::setw(36) << "\x1B[35m[START DATETIME]\033[0m" << _Time::s_datetime.getNowStr() << std::endl;
	std::cout << "\x1B[35m" << line << "\033[0m\n" << std::endl;

	if (logFile.is_open()) {
		logFile << std::boolalpha << std::left;
		logFile << (LOG_DEBUG_CHAR == 'D' ? "[DEBUG]" : "[RELEASE]") << std::endl;
#ifdef _MSC_FULL_VER
		logFile << std::setw(36) << "[VS STUDIO VERSION]" << _MSC_FULL_VER << " (1916: Visual Studio 17)" << std::endl;
#endif
#ifdef _MSVC_LANG
		logFile << std::setw(36) << "[C++ VERSION]" << _MSVC_LANG << std::endl;
#endif
		logFile << std::setw(36) << "[START DATETIME]" << _Time::s_datetime.getNowStr() << std::endl;
		logFile << line << std::endl;
	} else {

		std::cout << std::left 
			<< "\x1B[31m[" << _Time::s_time.getNowStr() << "]  " << "(ERROR)\n"
			<< "FAILED TO OPEN LOG FILE" << "\033[0m\n" << logFilePath << "\n";
			
		strcpy_s(commandBuffer, "pause");
		strcat_s(commandBuffer, NULL_FILE_REDIRECT);
		system(commandBuffer);
		memset(commandBuffer, 0, sizeof(commandBuffer));
	}
}


Log::Log(int threatLevel, int verboseLevel) 
	: showThreatLevel((ThreatLevels)threatLevel)
	, verboseLevel((VerboseLevels)verboseLevel) {
	
#	ifdef OVERWRITE_STL_SYNC
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
#	endif

	memset(commandBuffer, 0, sizeof(commandBuffer));
	bodyLen = 90;
	std::fill(line, line + 120, '_');

	strcpy_s(logFilePath, "logs");
	strcat_s(logFilePath, &DIR_DELIMITER);
	strcat_s(logFilePath, _Time::s_programStartTime.getStr());
	strcat_s(logFilePath, &DIR_DELIMITER);
	strcat_s(logFilePath, _Time::s_programStartTime.getStr());
	strcat_s(logFilePath, "_");
	strcat_s(logFilePath, &LOG_DEBUG_CHAR);
	strcat_s(logFilePath, ".log");

	this->startup();
}

Log::~Log() {
	info(__FUNCTION__, __LOG_FILENAME__, __LINE__, "Session ended");
	logFile.close();
}
