#ifndef TAG_READER_H
#define TAG_READER_H

#include <string>
#include <vector>

extern std::string title;
extern std::string artist;
extern std::string album;
extern std::string year;

struct TagMismatch {
    std::string filename;
    std::string artist;
    std::string album;
};

void readTag(const std::string& filePath);

void setAlbumArtist(const std::string& albumArtist);

void setAlbumName(const std::string& albumName);

void setReleaseYear(const std::string& albumYear);

bool checkUniformTags(const std::string& directoryPath);

std::vector<TagMismatch> verifyUniformTags(const std::string& directoryPath);

#endif // TAG_READER_H
