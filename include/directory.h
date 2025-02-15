#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>

extern std::string baseDirectory;

void setBaseDirectory(const std::string& newPath);

bool checkIfDirectoryExists(const std::string& directory);

void createDirectory(const std::string& directory);

void getFilesInDirectory(const std::string& directory);

void getDirectoriesInDirectory();

void analyzeFilesInDirectory();

std::string appendToDirectory(const std::string& directory, const std::string& append);

#endif // DIRECTORY_H
