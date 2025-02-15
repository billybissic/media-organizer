#include "files.h"
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <filesystem>

namespace fs = std::filesystem;

void copyFile(const std::string& source, const std::string& destination) {
	std::cout << "Copying file from " << source << " to " << destination << std::endl;
	
}

void copyFiles(const std::string& source, const std::string& destination) {
	std::cout << "Copying files from " << source << " to " << destination << std::endl;
}

void moveFile(const std::string& source, const std::string& destination) {
	std::cout << "Moving file from " << source << " to " << destination << std::endl;
}

void moveFiles(const std::string& source, const std::string& destination) {
	std::cout << "   [*] - Moving files from '" << source << "' to '" << destination << "'" << std::endl;
	//move only the files from source directory to destination directory
	try {
		for (const auto& entry : fs::directory_iterator(source)) {
			if (fs::is_regular_file(entry)) {
				std::string fileFolder = entry.path().string();
				std::string fileName = entry.path().filename().string();
				std::string destinationFile = destination + "/" + fileName;
				fs::rename(fileFolder, destinationFile);
				std::cout << "   [*] - Moved file: " << fileName << std::endl;
			}
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

}

void deleteFile(const std::string& filePath) {
	std::cout << "Deleting file " << filePath << std::endl;
	try {
		if (fs::remove(filePath)) {
			std::cout << "File deleted: " << filePath << std::endl;
		}
		else {
			std::cerr << "File not found: " << filePath << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error deleting file: " << e.what() << std::endl;
	}
}

void deleteFiles(const std::string& directoryPath) {
	std::cout << "Deleting files in directory " << directoryPath << std::endl;
}

void deleteEmptyDirectory(const std::string& directory) {
	std::cout << "Deleting empty directory " << directory << std::endl;
	try {
		if (fs::remove(directory)) {
			std::cout << "Directory deleted: " << directory << std::endl;
		}
		else {
			std::cerr << "Directory not found: " << directory << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error deleting directory: " << e.what() << std::endl;
	}
}

bool validateIfDirectoryIsEmpty(const std::string& directory) {
	std::cout << "Validating if directory is empty " << directory << std::endl;
	//check if the directory is empty
	try {
		if (fs::is_empty(directory)) {
			std::cout << "Directory is empty: " << directory << std::endl;
			return true;
		}
		else {
			std::cerr << "Directory is not empty: " << directory << std::endl;
			return false;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error validating if directory is empty: " << e.what() << std::endl;
	}

	return false;
}