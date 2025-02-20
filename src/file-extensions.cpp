#include "file-extensions.h"
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <algorithm>


namespace fs = std::filesystem;

std::vector<std::string> audioFileExtensions = { ".mp3", ".flac", ".wav", ".aac", ".m4a", ".ogg"};
std::vector<std::string> imageFileExtensions = { ".jpg", ".jpeg", ".png", ".bmp", ".gif" };

bool isAudioFileSupported(std::string extension) {
	for (const auto& audioExtension : audioFileExtensions) {
		if (extension == audioExtension) {
			//std::cout << "Audio file extension, " << extension << " is supported." << std::endl;
			return true;
		}
	}
	std::cout << "Audio file extension, " << extension << " is not supported." << std::endl;
	return false;
}
bool isImageFileSupported(std::string extension) {
	for (const auto& imageExtension : imageFileExtensions) {
		if (extension == imageExtension) {
			std::cout << "Image file extension is supported." << std::endl;
			return true;
		}
	}
	std::cout << "Image file extension is not supported." << std::endl;
	return false;
}

std::string getFileExtension(const std::string& filePath) {
	std::string extension = filePath.substr(filePath.find_last_of("."));
	return extension;
}

std::string findMostCommonFileExtensionInDirectory(const std::string& directory) {
	std::vector<std::string> fileExtensions;
	for (const auto& entry : fs::directory_iterator(directory)) {
		if (fs::is_regular_file(entry)) {
			std::string fileExtension = getFileExtension(entry.path().filename());
			fileExtensions.push_back(fileExtension);
		}
	}
	//find the most common file extension
	std::string mostCommonExtension;
	int mostCommonExtensionCount = 0;
	for (const auto& extension : fileExtensions) {
		int currentExtensionCount = std::count(fileExtensions.begin(), fileExtensions.end(), extension);
		if (currentExtensionCount > mostCommonExtensionCount) {
			mostCommonExtension = extension;
			mostCommonExtensionCount = currentExtensionCount;
		}
	}
	return mostCommonExtension;
}