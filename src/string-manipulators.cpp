
#include "string-manipulators.h"
#include <string>
#include <vector>

std::string toLower(const std::string& str) {
	std::string lowerStr = str;
	for (char& c : lowerStr) {
		c = tolower(c);
	}
	return lowerStr;
}

std::string toUpper(const std::string& str) {
	std::string upperStr = str;
	for (char& c : upperStr) {
		c = toupper(c);
	}
	return upperStr;
}

std::string trim(const std::string& str) {
	std::string trimmedStr = str;
	trimmedStr.erase(0, trimmedStr.find_first_not_of(" \t\n"));
	trimmedStr.erase(trimmedStr.find_last_not_of(" \t\n") + 1);
	return trimmedStr;
}

std::string removeFirstCharacter(const std::string& str) {
	std::string removedStr = str;
	removedStr.erase(0, 1);
	return removedStr;
}


