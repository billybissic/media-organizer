// include/file-extensions.h
#ifndef FILE_EXTENSIONS_H
#define FILE_EXTENSIONS_H

#include <string>
#include <vector>

std::vector<std::string> audioFileExtensions;
std::vector<std::string> imageFileExtensions;

bool isAudioFileSupported(std::string extension);
bool isImageFileSupported(std::string extension);
std::string getFileExtension(const std::string& filePath);

#endif