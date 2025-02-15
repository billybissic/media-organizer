// include/music-sort.h
#ifndef MUSIC_SORT_H
#define MUSIC_SORT_H

#include <string>

extern std::string destinationRootDirectory;

void checkIfArtistDirectoryExists(const std::string& artistDirectory);
void checkIfAlbumDirectoryExists(const std::string& albumDirectory);
void moveFilesToAlbumDirectory(const std::string& fileFolder);
void moveFolderToArtistDirectory(const std::string& fileFolder);
void createArtistDirectory(const std::string& artistDirectory);
void sortDirectoryOfAlbums(const std::string& unsortedDirectory, const std::string& destinationDirectory);

#endif
