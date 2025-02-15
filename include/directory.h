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

#endif // DIRECTORY_H
