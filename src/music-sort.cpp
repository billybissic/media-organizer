// src/music-sort.cpp
#include "directory.h"
#include "music-sort.h"
#include "tag-reader.h"
#include <iostream>
#include <filesystem>
#include "naming-convention.h"
#include "execute-conditions.h"
#include "files.h"
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
	std::string currentArtistDirectory = "";
	std::string currentAlbumDirectory = "";
	setNamingConvention();
	clearScreen();

	std::cout << "Validating unsorted files directory." << std::endl;
	if (checkIfDirectoryExists(unsortedDirectory)) {
		std::cout << "   Unsorted files directory: \"" << unsortedDirectory << "\" exists." << std::endl;

		if (validateIfDirectoryIsEmpty(unsortedDirectory)) {
			std::cout << "Directory is empty, no work to be done." << std::endl;
			return;
		}

		std::cout << "Validating destination directory." << std::endl;
		if (checkIfDirectoryExists(destinationDirectory)) {
			std::cout << "   Destination directory: \"" << destinationDirectory << "\" exists." << std::endl;

			clearScreen();

			//list the directories of unsorted albums from the unsorted directory
			for (const auto& entry : fs::directory_iterator(unsortedDirectory)) {
				if (fs::is_directory(entry)) {
					//store album_directory name
					std::string albumDirectory = entry.path().string();
					//extract the album name from the album_directory
					std::string albumDirectoryName = albumDirectory.substr(albumDirectory.find_last_of("/\\") + 1);
					clearScreen();
					std::cout << "Currently analyzing: " << albumDirectoryName << std::endl;
					
					std::cout << "   Full path: " << albumDirectory << std::endl;
					//list files in the albumDirectory

					if (!validateIfDirectoryIsEmpty(albumDirectory)) {
						
						for (const auto& albumEntry : fs::directory_iterator(albumDirectory)) {
							if (fs::is_regular_file(albumEntry.path())) {
								std::string fileFolder = albumEntry.path().string();
								/*if (verifyUniformTagsForAlbum(fileFolder)) {
									moveFilesToAlbumDirectory(fileFolder);
								}*/
								/*std::cout << "albumEntry: " << albumEntry << std::endl;
								std::cout << "fileFolder: " << fileFolder << std::endl;*/
							}
						}
					
						//check if all files have the same artist and album	
						if (checkUniformTags(albumDirectory)) {
							std::cout << "   [*] - All files have the same artist and album.\n";
							/* check if artist directory exists; then create it if not. */
							currentArtistDirectory = appendToDirectory(destinationDirectory, artist);
							if (checkIfDirectoryExists(currentArtistDirectory)) {
								std::cout << "   [*] - Artist directory, '" << currentArtistDirectory << "', exists." << std::endl;
							}
							else {
								if (isDryRun == false) {
									std::cout << "   [*] - Creating artist directory, '" << currentArtistDirectory << "'." << std::endl;
									createDirectory(currentArtistDirectory);
								}
							}
							/* generate album directory based on naming convention */
							currentAlbumDirectory = generateAlbumDirectoryName(artist, album, year);
							currentAlbumDirectory = appendToDirectory(currentArtistDirectory, currentAlbumDirectory);
							/* check if album directory exists; then create it if not. */
							std::cout << "   [*] - Validating if '" << currentAlbumDirectory << "' exists." << std::endl;
							/* validate directories were created properly; then move files if yes */
							if (checkIfDirectoryExists(currentAlbumDirectory)) {
								std::cout << "   [*] - Album directory, '" << currentAlbumDirectory << "', exists." << std::endl;
							}
							else {
								if (isDryRun == false) {
									std::cout << "   [*] - Creating album directory, '" << currentAlbumDirectory << "'." << std::endl;
									createDirectory(currentAlbumDirectory);
								}
								if (checkIfDirectoryExists(currentAlbumDirectory)) {
									std::cout << "   [*] - Album directory, '" << currentAlbumDirectory << "', created successfully." << std::endl;
								}
							}

							/* move files to album directory */
							if (isDryRun == false) {
								moveFiles(albumDirectory, currentAlbumDirectory);
							}

							/* destroy source directory */
							if (isDryRun == false) {
								if(validateIfDirectoryIsEmpty(albumDirectory)) {
									deleteEmptyDirectory(albumDirectory);
								}
							}

						}
						else {
							std::cout << "Mismatch detected in artist or album tags.\n";
							std::cout << "Would you like to update the artist and album tags? (y/n): ";
						}
					}
					else {
						std::cout << "Directory is empty, no work to be done." << std::endl;
					}
				}
			}
		}
		else {
			std::cout << "Destination directory\"" << destinationDirectory << "\" does not exist, cannot continue.";
			return;
		}
	}
    else {
		std::cout << "Unsorted files directory\"" << unsortedDirectory << "\" does not exist, cannot continue.";
		return;
    }
}