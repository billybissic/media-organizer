#include <string>
#include <vector>

std::vector<std::string> audioFileExtensions = { ".mp3", ".flac", ".wav", ".aac", ".m4a" };
std::vector<std::string> imageFileExtensions = { ".jpg", ".jpeg", ".png", ".bmp", ".gif" };

bool isAudioFileSupported(std::string extension) {
	for (const auto& audioExtension : audioFileExtensions) {
		if (extension == audioExtension) {
			std::cout << "Audio file extension is supported.\n";
			return true;
		}
	}
	std::cout << "Audio file extension is not supported.\n";
	return false;
}
bool isImageFileSupported(std::string extension) {
	for (const auto& imageExtension : imageFileExtensions) {
		if (extension == imageExtension) {
			std::cout << "Image file extension is supported.\n";
			return true;
		}
	}
	std::cout << "Image file extension is not supported.\n";
	return false;
}

std::string getFileExtension(const std::string& filePath) {
	std::string extension = filePath.substr(filePath.find_last_of("."));
	return extension;
}