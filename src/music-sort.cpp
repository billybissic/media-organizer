// src/music-sort.cpp
#include "directory.h"
#include "music-sort.h"
#include "tag-reader.h"
#include <iostream>
#include <filesystem>
#include "naming-convention.h"
// Define a global variable for the directory to send sorted music to
std::string destinationRootDirectory = "";

namespace fs = std::filesystem;

bool checkIfArtistExists(const std::string& artistDirectory) {
   return checkIfDirectoryExists(artistDirectory);
}

bool checkIfAlbumExists(const std::string& albumDirectory) {
   return checkIfDirectoryExists(albumDirectory);
}

bool verifyUniformTagsForAlbum(const std::string& albumDirectory) {
   if (checkUniformTags(albumDirectory)) {
      std::cout << "All files have the same artist and album.\n";
      return true;
   } else {
      std::cout << "Mismatch detected in artist or album tags.\n";
      return false;
   }
}

void sortDirectoryOfAlbums(const std::string& unsortedDirectory, const std::string& destinationDirectory) {
    setNamingConvention();
	if (checkIfDirectoryExists(unsortedDirectory)) {
		std::cout << "Unsorted files directory\"" << unsortedDirectory << "\" exists.";
		if (checkIfDirectoryExists(destinationDirectory)) {
			std::cout << "Destination directory\"" << destinationDirectory << "\" exists.";

			//list the directories of unsorted albums from the unsorted directory
			for (const auto& entry : fs::directory_iterator(unsortedDirectory)) {
				if (fs::is_directory(entry)) {
					//store album_directory name
					std::string albumDirectory = entry.path().string();
					//extract the album name from the album_directory
					std::string albumDirectoryName = albumDirectory.substr(albumDirectory.find_last_of("/\\") + 1);
					std::cout << "albumDirectoryName: " << albumDirectoryName << std::endl;

					std::cout << "albumDirectory: " << albumDirectory << std::endl;
					//list files in the albumDirectory
					for (const auto& albumEntry : fs::directory_iterator(albumDirectory)) {
						if (fs::is_regular_file(albumEntry.path())) {
							std::string fileFolder = albumEntry.path().string();
							/*if (verifyUniformTagsForAlbum(fileFolder)) {
								moveFilesToAlbumDirectory(fileFolder);
							}*/
							std::cout << "albumEntry: " << albumEntry << std::endl;
							std::cout << "fileFolder: " << fileFolder << std::endl;
						}
					}
				}
			}
		}
		else {
			std::cout << "Destination directory\"" << destinationDirectory << "\" does not exist.";
			//createDirectory(destinationDirectory);
		}
	}
    else {
		std::cout << "Unsorted files directory\"" << unsortedDirectory << "\" does not exist.";
    }
}