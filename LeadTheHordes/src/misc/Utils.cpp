#include "Hordes_pch.h"
#include "Utils.h"

#include <unordered_map>
#include <string>
#include <fstream>
#include <regex>


namespace Utils {


bool str2bool(std::string& str) {
	if (str == "true" || str == "True" || str == "1") {
		return true;
	} else if (str == "false" || str == "False" || str == "0") {
		return false;
	} else {
		throw std::invalid_argument( "The string doesn't conform to neither true nor false");
	}
}

bool str2bool(const char* str) {
	char str_bak[6] = { '\0', '\0', '\0', '\0', '\0', '\0' };

	if ((std::strcmp(str_bak, "true") == 0) || (std::strcmp(str_bak, "True") == 0) || (std::strcmp(str_bak, "1") == 0)) {
		return true;
	}
	if ((std::strcmp(str_bak, "false") == 0) || (std::strcmp(str_bak, "False") == 0) || (std::strcmp(str_bak, "0") == 0)) {
		return false;
	}

	throw std::invalid_argument("The char array doesn't conform to neither true nor false.");
}




std::unordered_map<std::string, std::string> Utils::mapFromIni(std::string path, std::string errorKey) {
	std::ifstream ifs = std::ifstream(path);

	std::string line = std::string();
	std::unordered_map<std::string, std::string> retval = std::unordered_map<std::string, std::string>();

	// pattern for ini files
	std::regex match_pattern = std::regex("^[ \\t]*([a-zA-Z_][\\w]*)[^\\S\\n]*=[^\\S\\n]*(?:(?:\"([\\S\\t ]*)\")|([\\w\\.:\\/\\-\\\\]+))", std::regex_constants::optimize);
	std::smatch match = std::smatch();

	if (!ifs.is_open()) {
		retval.insert_or_assign(errorKey, "Could not open the file! ifs.is_open() == false");
	} else {
		while (ifs.good()) {
			std::getline(ifs, line);
			std::regex_search(line, match, match_pattern);

			// match[2] is for values in "", match[3] is for other values
			if (match.size() >= 3 && match[2].matched) {
				retval.insert_or_assign(match[1], match[2]);
			}

			if (match.size() >= 4 && match[3].matched) {
				retval.insert_or_assign(match[1], match[3]);
			}
		}
	}

	ifs.close();

	return retval;
}

}