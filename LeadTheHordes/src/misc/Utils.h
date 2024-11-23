#pragma once


namespace Utils {

bool str2bool(std::string &str);
bool str2bool(const char *str);

std::unordered_map<std::string, std::string> mapFromIni(std::string path, std::string errorKey = "__error__");

}
