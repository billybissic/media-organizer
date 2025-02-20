// src/music-sort.cpp
#include "directory.h"
#include "files.h"
#include "file-extensions.h"
#include "tag-reader.h"
#include "naming-convention.h"
#include "execute-conditions.h"
#include "string-manipulators.h"
#include "music-sort.h"
#include <iostream>
#include <filesystem>

// Define a global variable for the directory to send sorted music to
std::string destinationRootDirectory = "";

namespace fs = std::filesystem;
CommonTags commonTags;

bool checkIfArtistExists(const std::string& artistDirectory) {
   return checkIfDirectoryExists(artistDirectory);
}

bool checkIfAlbumExists(const std::string& albumDirectory) {
   return checkIfDirectoryExists(albumDirectory);
}

bool verifyUniformTagsForAlbum(const std::string& albumDirectory) {
   if (checkUniformTags(albumDirectory)) {
	   std::cout << "All files have the same artist and album." << std::endl;
      return true;
   } else {
      std::cout << "Mismatch detected in artist or album tags." << std::endl;
      return false;
   }
}

bool isSoundTrack(const std::string& album) {
	std::string albumName = toLower(album);
	if (albumName.find("ost") != std::string::npos || albumName.find("soundtrack") != std::string::npos) {
		return true;
	}
	return false;
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
							std::cout << "   [*] - All files have the same artist and album." << std::endl;
							/* check if artist directory exists; then create it if not. */
													/* if currentAlbumDirectory contains OST or SoundTrack, no matter what case the letters are in change the artist to SoundTrack*/
							std::cout << "   [*] - Album" << album << std::endl;
							if (isSoundTrack(album)) {
								std::cout << "   [*] - Album name contains 'OST' or 'SoundTrack'." << std::endl;
								currentArtistDirectory = appendToDirectory(destinationDirectory, "SoundTrack");
							}
							else {
								/* create artist directory & validate if created */
								std::cout << "   [*] - Album name did not contain 'OST' or 'SoundTrack'." << std::endl;
								currentArtistDirectory = appendToDirectory(destinationDirectory, artist);
							}

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
							if (selectedConvention > 2) {
								std::string commonFileType = findMostCommonFileExtensionInDirectory(albumDirectory);
								if (!commonFileType.empty()) {
									commonFileType = toUpper(commonFileType);
									commonFileType = removeFirstCharacter(commonFileType);
									std::cout << "   [*] - Common file type: " << commonFileType << std::endl;
								}
								currentAlbumDirectory = generateAlbumDirectoryName(artist, album, year, commonFileType);
							}
							else {
								currentAlbumDirectory = generateAlbumDirectoryName(artist, album, year);
							}

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
							std::cout << "Mismatch detected in artist or album tags." << std::endl;;
							std::cout << "Would you like to update the artist and album tags? (y/n): " << std::endl;
							std::string response;
							std::cin >> response;
							if (response == "y") {
								std::vector<TagMismatch> mismatchingTags = verifyUniformTags(albumDirectory);
								for (const auto& mismatch : mismatchingTags) {
									std::cout << "Mismatch detected in " << mismatch.filename << std::endl;
									std::cout << "Current artist: '" << mismatch.artist << "'." << std::endl;
									std::cout << "Current album: '" << mismatch.album << "'." << std::endl;
									std::cout << "Would you like to update the artist and album tags? (y/n): " << std::endl;
									std::cin >> response;
									std::cin.ignore();

									if (response == "y") {
										std::string newArtist, newAlbum;
										std::cout << "Enter new artist: ";
										std::getline(std::cin, newArtist);

										std::cout << "Enter new album: ";
										std::getline(std::cin, newAlbum);
										
										std::string filePathToUpdateTags = appendToDirectory(albumDirectory, mismatch.filename);
										updateTags(filePathToUpdateTags, newArtist, newAlbum);
									}
								}
							}
							else {
								std::cout << "Skipping album." << std::endl;
								// treat as compilation album
								if (allowCompilations) {
									std::cout << "Allowing compilation albums." << std::endl;
									//find the common artist and album name
									findTheMostCommonTags(albumDirectory);
									if (commonTags.artist.empty() || commonTags.album.empty()) {
										std::cout << "Cannot determine common artist and album name." << std::endl;
										std::cout << "Skipping album." << std::endl;
										continue;
									}
									else {
										std::cout << "Common artist: " << commonTags.artist << std::endl;
										std::cout << "Common album: " << commonTags.album << std::endl;
										//create artist directory
										currentArtistDirectory = appendToDirectory(destinationDirectory, commonTags.artist);
										if (checkIfDirectoryExists(currentArtistDirectory)) {
											std::cout << "Artist directory, '" << currentArtistDirectory << "', exists." << std::endl;
										}
										else {
											if (isDryRun == false) {
												std::cout << "Creating artist directory, '" << currentArtistDirectory << "'." << std::endl;
												createDirectory(currentArtistDirectory);
											}
										}
										//create album directory
										currentAlbumDirectory = generateAlbumDirectoryName(commonTags.artist, commonTags.album, year);
										currentAlbumDirectory = appendToDirectory(currentArtistDirectory, currentAlbumDirectory);
										if (checkIfDirectoryExists(currentAlbumDirectory)) {
											std::cout << "Album directory, '" << currentAlbumDirectory << "', exists." << std::endl;
										}
										else {
											if (isDryRun == false) {
												std::cout << "Creating album directory, '" << currentAlbumDirectory << "'." << std::endl;
												createDirectory(currentAlbumDirectory);
											}
										}
										//move files to album directory
										if (isDryRun == false) {
											moveFiles(albumDirectory, currentAlbumDirectory);
										}
										//destroy source directory
										if (isDryRun == false) {
											if (validateIfDirectoryIsEmpty(albumDirectory)) {
												deleteEmptyDirectory(albumDirectory);
											}
										}
									}
									//check if the album name has soundtrack in it
								}
							}
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



void sortDirectoryOfAudioFiles(const std::string& unsortedDirectory, const std::string& destinationDirectory) {
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
			//list the files of unsorted albums from the unsorted directory
			for (const auto& entry : fs::directory_iterator(unsortedDirectory)) {
				if (fs::is_regular_file(entry.path())) {
					std::string fileFolder = entry.path().string();
					std::cout << "Currently analyzing: " << entry.path().filename() << std::endl;
					/* validate if media file is supported file extension*/
					std::string currentFileExtension = getFileExtension(entry.path().filename());
					if (isAudioFileSupported(currentFileExtension)) {
						/* get tag information if it is a supported file extension */
						readTag(fileFolder);

						/* check if artist, album, and year is blank */
						if (artist.empty() || album.empty() || year.empty()) {
							/* check if user wants to update tag information manually if no skip file */
							std::string response;
							std::cout << "   [*] - Artist, album, or year tags are blank." << std::endl;
							std::cout << " Artist: " << artist << std::endl;
							std::cout << " Album: " << album << std::endl;
							std::cout << " Year: " << year << std::endl;
							std::cout << "   [*] - Would you like to update the artist and album tags? (y/n): " << std::endl;
							std::getline(std::cin, response);

							if (response == "y") {
								std::string newArtist, newAlbum, newYear;
								std::cout << "   [*] - Enter new artist: ";
								std::getline(std::cin, newArtist);
								std::cout << "   [*] - Enter new album: ";
								std::getline(std::cin, newAlbum);
								std::cout << "   [*] - Enter new year: ";
								std::getline(std::cin, newYear);
								artist = newArtist;
								album = newAlbum;
								year = newYear;
							}
							else {
								std::cout << "   [*] - Skipping file: " << entry.path().filename() << std::endl;
								std::cout << "Would you like to try to pull some of the information from the file names? [y/n]" << std::endl;
								std::string response;
								std::getline(std::cin, response);

								continue;
							}
						}

						
						/* if currentAlbumDirectory contains OST or SoundTrack, no matter what case the letters are in change the artist to SoundTrack*/
						std::cout << "   [*] - Album " << album << std::endl;
						if (isSoundTrack(album)) {
							std::cout << "   [*] - Album name contains 'OST' or 'SoundTrack'." << std::endl;
							currentArtistDirectory = appendToDirectory(destinationDirectory, "SoundTracks");
						}
						else {
							/* create artist directory & validate if created */
							std::cout << "   [*] - Album name did not contain 'OST' or 'SoundTrack'." << std::endl;
							currentArtistDirectory = appendToDirectory(destinationDirectory, artist);
						}
						
						if (checkIfDirectoryExists(currentArtistDirectory)) {
							std::cout << "   [*] - Artist directory, '" << currentArtistDirectory << "', exists." << std::endl;
						}
						else {
							if (isDryRun == false) {
								std::cout << "   [*] - Creating artist directory, '" << currentArtistDirectory << "'." << std::endl;
								createDirectory(currentArtistDirectory);
							}
						}

						/* create album directory */
						currentAlbumDirectory = generateAlbumDirectoryName(artist, album, year);
						
						/* append album directory to artist directory */
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
						/* move file to album directory */
						if (isDryRun == false) {
							moveFiles(fileFolder, currentAlbumDirectory);
						}
						/* destroy source directory */
						if (isDryRun == false) {
							deleteFile(fileFolder);
						}
					}
					else {
						std::cout << "   [*] - Skipping file: " << entry.path().filename() << std::endl;
					}
				}
			}
		}
		else {
			std::cout << "Destination directory\"" << destinationDirectory << "\" does not exist, cannot continue.";
			return;
		}
	}
}