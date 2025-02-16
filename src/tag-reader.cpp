// src/tag-reader.cpp
#include "tag-reader.h"
#include <iostream>
#include <filesystem>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>
#include <vector>

namespace fs = std::filesystem;

std::string title = "";
std::string artist = "";
std::string album = "";
std::string year = "";

void readTag(const std::string& filePath) {
   TagLib::FileRef file(filePath.c_str());

    if (!file.isNull() && file.tag()) {
        TagLib::Tag *tag = file.tag();

        std::cout << "Title:  " << tag->title().to8Bit(true) << std::endl;
	//setAlbumName(tag->title().to8Bit(true))
        std::cout << "Artist: " << tag->artist().to8Bit(true) << std::endl;
	setAlbumArtist(tag->title().to8Bit(true));
        std::cout << "Album:  " << tag->album().to8Bit(true) << std::endl;
	setAlbumName(tag->title().to8Bit(true));
        std::cout << "Year:   " << tag->year() << std::endl;
	setReleaseYear(std::to_string(tag->year()));
    } else {
        std::cerr << "Error reading ID3 tags from " << filePath << std::endl;
    }
}

void setAlbumArtist(const std::string& albumArtist) {
   artist = albumArtist;
}

void setAlbumName(const std::string& albumName) {
   album = albumName;
}

void setReleaseYear(const std::string& albumYear) {
   year = albumYear;
}

bool checkUniformTags(const std::string& directoryPath) {
    std::string commonArtist, commonAlbum;
    std::int16_t commonYear;
    bool firstFile = true;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            TagLib::FileRef file(entry.path().c_str());

            if (!file.isNull() && file.tag()) {
                std::string artist = file.tag()->artist().to8Bit(true);
				std::string album = file.tag()->album().to8Bit(true);
				std::int16_t year = file.tag()->year();

                if (file.file()) {
                    TagLib::PropertyMap properties = file.file()->properties();
                    if (properties.contains("ALBUMARTIST")) {
                        artist = properties["ALBUMARTIST"].toString().to8Bit(true);
                    }
                    else if (properties.contains("ALBUM ARTIST")) {
                        artist = properties["ALBUM ARTIST"].toString().to8Bit(true);
                    }
                    else {
                        artist = file.tag()->artist().to8Bit(true);
                    }
                }

                if (firstFile) {
                    commonArtist = artist;
                    commonAlbum = album;
                    commonYear = year;
                    firstFile = false;
                } else {
                    if (artist != commonArtist || album != commonAlbum || year != commonYear) {
                        std::cerr << "Mismatch found: " << entry.path().filename() << std::endl;
                        std::cerr << "Expected: " << commonArtist << " - " << commonAlbum << " - " << commonYear << std::endl;
						std::cerr << "Found: " << artist << " - " << album << " - " << year << std::endl;
                        return false;
                    }
                }
            }
        }
    }
	setAlbumArtist(commonArtist);
	setAlbumName(commonAlbum);
	setReleaseYear(std::to_string(commonYear));
    return true;
}

// Returns a list of mismatches instead of a boolean
std::vector<TagMismatch> verifyUniformTags(const std::string& directoryPath) {
    std::string commonArtist, commonAlbum;
    bool firstFile = true;
    std::vector<TagMismatch> mismatches;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            TagLib::FileRef file(entry.path().c_str());

            if (!file.isNull() && file.tag()) {
                std::string artist = file.tag()->artist().to8Bit(true);
                std::string album = file.tag()->album().to8Bit(true);

                if (firstFile) {
                    commonArtist = artist;
                    commonAlbum = album;
                    firstFile = false;
                }
                else {
                    if (artist != commonArtist || album != commonAlbum) {
                        mismatches.push_back({ entry.path().filename().string(), artist, album });
                    }
                }
            }
        }
    }
    return mismatches;
}