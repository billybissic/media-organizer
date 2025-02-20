#ifndef TAG_READER_H
#define TAG_READER_H

#include "common-tags.h"
#include <string>
#include <vector>

extern std::string title;
extern std::string artist;
extern std::string album;
extern std::string year;

extern CommonTags commonTags;

struct TagMismatch {
    std::string filename;
    std::string artist;
    std::string album;
};

struct Tag {
	std::string title;
	std::string artist;
	std::string album;
	std::string year;
};

void readTag(const std::string& filePath);

void setAlbumArtist(const std::string& albumArtist);

void setAlbumName(const std::string& albumName);

void setReleaseYear(const std::string& albumYear);

bool checkUniformTags(const std::string& directoryPath);

std::vector<TagMismatch> verifyUniformTags(const std::string& directoryPath);

void updateTags(const std::string& filePath, const std::string& newArtist, const std::string& newAlbum);

void updateTagsInDirectory(const std::string& directoryPath, const std::string& newArtist, const std::string& newAlbum);

void readTagsFromFileNamingConvention(const std::string& filePath);

void findTheMostCommonTags(const std::string& directoryPath);

void setCommonTags(const std::string& artist, const std::string& album, const std::string& year);

std::vector<std::string> findFilesWithMatchingArtistAndAlbum(const std::string& directoryPath);

#endif // TAG_READER_H
