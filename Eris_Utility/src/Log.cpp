#include <sstream>
#include <string_view>

#include <fstream>
#include <iostream>

#include "Eris_Utility/Log.h"



namespace EUtil {

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


	commandBuffer  = "mkdir logs";
	commandBuffer += DIR_DELIMITER;
	commandBuffer += TimeFormatter::s_programStart.getStr();
	commandBuffer += "_";
	commandBuffer += LOG_DEBUG_CHAR;
	commandBuffer += " ";
	commandBuffer += NULL_FILE_REDIRECT;

	system(commandBuffer.c_str());

	commandBuffer = "";

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
	filePath += TimeFormatter::s_programStart.getStr();
	filePath += "_";
	filePath += LOG_DEBUG_CHAR;
	filePath += DIR_DELIMITER;
	filePath += filePrefix;
	filePath += TimeFormatter::s_programStart.getStr();
	filePath += "_";
	filePath += LOG_DEBUG_CHAR;
	filePath += ".log";

	strcpy_s(this->logFilePath, filePath.c_str());

	//strcpy_s(logFilePath, "logs");
	//strcat_s(logFilePath, DIR_DELIMITER);
	//strncat_s(logFilePath, TimeFormatter::s_programStart.getStr(), std::strlen(TimeFormatter::s_programStart.getStr()));
	//strcat_s(logFilePath, "_");
	//strcat_s(logFilePath, LOG_DEBUG_CHAR);
	//strcat_s(logFilePath, DIR_DELIMITER);
	//strcat_s(logFilePath, "EUtil__");
	//strncat_s(logFilePath, TimeFormatter::s_programStart.getStr(), std::strlen(TimeFormatter::s_programStart.getStr()));
	//strcat_s(logFilePath, "_");
	//strcat_s(logFilePath, LOG_DEBUG_CHAR);
	//strcat_s(logFilePath, ".log");

	logFile.open(logFilePath);

	std::cout << std::boolalpha << std::left;
	std::cout << (LOG_DEBUG_CHAR == "D" ? "\x1B[35m[DEBUG]\033[0m" : "\x1B[35m[RELEASE]\033[0m") << std::endl;
	
	#ifdef _MSC_FULL_VER
		std::cout << std::setw(36) << "\x1B[35m[VS STUDIO VERSION]\033[0m" << _MSC_FULL_VER << " (1916: Visual Studio 17)" << std::endl;
	#endif
	
	#ifdef _MSVC_LANG
		std::cout << std::setw(36) << "\x1B[35m[C++ VERSION]\033[0m" << _MSVC_LANG << std::endl;
	#endif

	std::cout << std::setw(36) << "\x1B[35m[START DATETIME]\033[0m" << TimeFormatter::s_datetime.getNowStr() << std::endl;
	std::cout << "\x1B[35m" << line << "\033[0m\n" << std::endl;

	if (logFile.is_open()) {
		logFile << std::boolalpha << std::left;
		logFile << (LOG_DEBUG_CHAR == "D" ? "[DEBUG]" : "[RELEASE]") << std::endl;
	
		#ifdef _MSC_FULL_VER
				logFile << std::setw(36) << "[VS STUDIO VERSION]" << _MSC_FULL_VER << " (1916: Visual Studio 17)" << std::endl;
		#endif
		
		#ifdef _MSVC_LANG
				logFile << std::setw(36) << "[C++ VERSION]" << _MSVC_LANG << std::endl;
		#endif

		logFile << std::setw(36) << "[START DATETIME]" << TimeFormatter::s_datetime.getNowStr() << std::endl;
		logFile << line << std::endl;
	} else {

		std::cout << std::left 
			<< "\x1B[31m[" << TimeFormatter::s_time.getNowStr() << "]  " << "(ERROR)\n"
			<< "FAILED TO OPEN LOG FILE" << "\033[0m\n" << logFilePath << "\n";

		commandBuffer = "pause ";
		commandBuffer = NULL_FILE_REDIRECT;

		system(commandBuffer.c_str());
		commandBuffer = "";
	}
}

}