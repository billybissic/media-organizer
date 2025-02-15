// include/file-extensions.h
#ifndef FILE_EXTENSIONS_H
#define FILE_EXTENSIONS_H

#include <string>
#include <vector>

void copyFile(const std::string& source, const std::string& destination);
void copyFiles(const std::string& source, const std::string& destination);
void moveFile(const std::string& source, const std::string& destination);
void moveFiles(const std::string& source, const std::string& destination);
void deleteFile(const std::string& filePath);
void deleteFiles(const std::string& directoryPath);
void deleteEmptyDirectory(const std::string& directoryPath);
bool validateIfDirectoryIsEmpty(const std::string& directoryPath);

#endif