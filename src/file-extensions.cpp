#include "file-extensions.h"
#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> audioFileExtensions = { ".mp3", ".flac", ".wav", ".aac", ".m4a" };
std::vector<std::string> imageFileExtensions = { ".jpg", ".jpeg", ".png", ".bmp", ".gif" };

bool isAudioFileSupported(std::string extension) {
	for (const auto& audioExtension : audioFileExtensions) {
		if (extension == audioExtension) {
			std::cout << "Audio file extension, " << extension << " is supported." << std::endl;
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