#pragma once

//<3// thanks to https://codereview.stackexchange.com/questions/187183/create-a-c-string-using-printf-style-formatting printf-like variadic templates

namespace ELog {

template<typename Func, typename File, typename H, typename B>
void Log::info(Func func_name, File file_name, int codeline, H head, B body, ...) {
	char buf[256];

	if constexpr (std::is_same_v<B, const char*>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body, args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else if constexpr (std::is_same_v<B, std::string>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body.c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else {
		std::ostringstream body_os; // convert body to string since we need to do a string check
		body_os << body;

		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body_os.str().c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	}

	if (showThreatLevel == InfoLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[36m[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(INFO)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";

			logFile << std::left
				<< "[" << ELog::TimeFormatter::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(INFO)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		if (verboseLevel == FullVerbose && buf[0] != '\0') {
			std::cout	<< buf << "\n";
			logFile		<< buf << "\n";
		}
		std::cout << "\x1B[36m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}

template<typename Func, typename File, typename H>
void Log::info(Func func_name, File file_name, int codeline, H head) {
	if (showThreatLevel == InfoLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[36m[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(INFO)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";

			logFile << std::left
				<< "[" << ELog::TimeFormatter::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(INFO)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		std::cout << "\x1B[36m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}



template<typename Func, typename File, typename H, typename B>
void Log::success(Func func_name, File file_name, int codeline, H head, B body, ...) {
	char buf[256];

	if constexpr (std::is_same_v<B, const char*>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body, args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else if constexpr (std::is_same_v<B, std::string>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body.c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else {
		std::ostringstream body_os; // convert body to string since we need to do a string check
		body_os << body;

		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body_os.str().c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	}

	if (showThreatLevel == InfoLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[32m[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(SUCCESS)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";
			logFile << std::left
				<< "[" << ELog::TimeFormatter::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(SUCCESS)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		if (verboseLevel == FullVerbose && buf[0] != '\0') {
			std::cout	<< buf << "\n";
			logFile		<< buf << "\n";
		}
		std::cout << "\x1B[32m" << this->line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}

template<typename Func, typename File, typename H>
void Log::success(Func func_name, File file_name, int codeline, H head) {
	if (showThreatLevel == InfoLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[32m[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(SUCCESS)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";
			logFile << std::left
				<< "[" << ELog::TimeFormatter::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(SUCCESS)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		std::cout << "\x1B[32m" << this->line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}



template<typename Func, typename File, typename H, typename B>
void Log::warn(Func func_name, File file_name, int codeline, H head, B body, ...) {
	char buf[256];

	if constexpr (std::is_same_v<B, const char*>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body, args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else if constexpr (std::is_same_v<B, std::string>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body.c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else {
		std::ostringstream body_os; // convert body to string since we need to do a string check
		body_os << body;

		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body_os.str().c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	}

	if (showThreatLevel >= WarningLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[33m[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(WARNING)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";
			logFile << std::left
				<< "[" << ELog::TimeFormatter::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(WARNING)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		if (verboseLevel == FullVerbose && buf[0] != '\0') {
			std::cout	<< buf << "\n";
			logFile		<< buf << "\n";
		}
		std::cout << "\x1B[33m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";

		logFile.flush();
	}
}

template<typename Func, typename File, typename H>
void Log::warn(Func func_name, File file_name, int codeline, H head) {
	if (showThreatLevel >= WarningLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[33m[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(WARNING)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";
			logFile << std::left
				<< "[" << ELog::TimeFormatter::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(WARNING)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		std::cout << "\x1B[33m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";

		logFile.flush();
	}
}



template<typename Func, typename File, typename H, typename B>
void Log::error(Func func_name, File file_name, int codeline, H head, B body, ...) {
	char buf[256];

	if constexpr (std::is_same_v<B, const char*>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body, args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else if constexpr (std::is_same_v<B, std::string>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body.c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else {
		std::ostringstream body_os; // convert body to string since we need to do a string check
		body_os << body;

		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body_os.str().c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	}

	if (verboseLevel >= LowVerbose) {
		std::cout << std::left 
			<< "\x1B[31m[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
			<< std::setw(15) << "(ERROR)"
			<< std::setw(65) << func_name
			<< file_name << ":" << codeline << "\n"
			<< head	<< "\033[0m\n";
		logFile << std::left
			<< "[" << ELog::TimeFormatter::s_time.getNowStr()<< "]  "
			<< std::setw(15) << "(ERROR)"
			<< std::setw(65) << func_name
			<< file_name << ":" << codeline << "\n"
			<< head	<< "\n";
	}
	if (verboseLevel == FullVerbose && buf[0] != '\0') {
		std::cout	<< buf << "\n";
		logFile		<< buf << "\n";
	}
	std::cout << "\x1B[31m" << line << "\033[0m\n\n";
	logFile << line << "\n\n";
	logFile.flush();
}

template<typename Func, typename File, typename H>
void Log::error(Func func_name, File file_name, int codeline, H head) {
	char buf[256];

	if (verboseLevel >= LowVerbose) {
		std::cout << std::left 
			<< "\x1B[31m[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
			<< std::setw(15) << "(ERROR)"
			<< std::setw(65) << func_name
			<< file_name << ":" << codeline << "\n"
			<< head	<< "\033[0m\n";
		logFile << std::left
			<< "[" << ELog::TimeFormatter::s_time.getNowStr()<< "]  "
			<< std::setw(15) << "(ERROR)"
			<< std::setw(65) << func_name
			<< file_name << ":" << codeline << "\n"
			<< head	<< "\n";
	}
	std::cout << "\x1B[31m" << line << "\033[0m\n\n";
	logFile << line << "\n\n";
	logFile.flush();
}



template<typename Func, typename File, typename H, typename B>
void Log::assert_(Func func_name, File file_name, int codeline, bool condition, H head, B body, ...) {
	if (condition) {
		char buf[256];

		if constexpr (std::is_same_v<B, const char*>) {
			va_list args;
			va_start(args, body);
			const int r = std::vsnprintf(buf, sizeof buf, body, args);
			va_end(args);
			if (r < 0)
				throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
		} else if constexpr (std::is_same_v<B, std::string>) {
			va_list args;
			va_start(args, body);
			const int r = std::vsnprintf(buf, sizeof buf, body.c_str(), args);
			va_end(args);
			if (r < 0)
				throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
		} else {
			std::ostringstream body_os; // convert body to string since we need to do a string check
			body_os << body;

			va_list args;
			va_start(args, body);
			const int r = std::vsnprintf(buf, sizeof buf, body_os.str().c_str(), args);
			va_end(args);
			if (r < 0)
				throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
		}

		if (verboseLevel >= LowVerbose) {
			std::cout << std::left
				<< "\x1B[31m[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(ASSERTION)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head << "\033[0m\n";
			logFile << std::left
				<< "[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(ASSERTION)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head << "\n";
		}
		if (verboseLevel == FullVerbose && buf[0] != '\0') {
			std::cout	<< buf << "\n";
			logFile		<< buf << "\n";
		}
		std::cout << "\x1B[31m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}

template<typename Func, typename File, typename H>
void Log::assert_(Func func_name, File file_name, int codeline, bool condition, H head) {
	if (condition) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[31m[" << ELog::TimeFormatter::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(ASSERTION)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";
			logFile << std::left
				<< "[" << ELog::TimeFormatter::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(ASSERTION)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		std::cout << "\x1B[31m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}
}