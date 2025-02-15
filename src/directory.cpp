// src/directory.cpp
#include "directory.h"
#include <iostream>
#include <filesystem>

std::string baseDirectory = "";

namespace fs = std::filesystem;

bool checkIfDirectoryExists(const std::string& directory) {
   return fs::exists(directory) && fs::is_directory(directory);
}

void setBaseDirectory(const std::string& newPath) {
   baseDirectory = newPath;
}

void getFilesInDirectory(const std::string& directory) {
    try {
       for (const auto& entry : fs::directory_iterator(directory)) {
          if (!fs::is_directory(entry)) {
	     std::cout << entry.path().filename() << std::endl;
	  }
       }
       std::cout << "Directory in directory!" << std::endl;
    } catch (const fs::filesystem_error& e) {
       std::cerr << "Error: " << e.what() << std::endl;
    }
}

void getDirectoriesInDirectory() {
    try {
       for (const auto& entry : fs::directory_iterator(baseDirectory)) {
          if (fs::is_directory(entry)) {
             std::cout << entry.path().filename() << std::endl;
          }
       }
       std::cout << "Files in directory!" << std::endl;
    } catch (const fs::filesystem_error& e) {
       std::cerr << "Error: " << e.what() << std::endl;
    }
}
