// include/files.h
#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>

extern std::vector<std::string> fileNamingConventions;
extern std::string selectedFileNamingConvention;

void copyFile(const std::string& source, const std::string& destination);
void copyFiles(const std::string& source, const std::string& destination);
void moveFile(const std::string& source, const std::string& destination);
void moveFiles(const std::string& source, const std::string& destination);
void deleteFile(const std::string& filePath);
void deleteFiles(const std::string& directoryPath);
void deleteEmptyDirectory(const std::string& directoryPath);
bool validateIfDirectoryIsEmpty(const std::string& directoryPath);
void setFileNamingConvention(const std::string& namingConvention);
void displayFileNamingConventions();
std::string getFileNamingConvention();

#endif