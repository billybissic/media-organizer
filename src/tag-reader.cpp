// src/tag-reader.cpp
#include "common-tags.h"
#include "tag-reader.h"
#include <iostream>
#include <filesystem>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>
#include <vector>
#include "file-extensions.h"

namespace fs = std::filesystem;

std::string title = "";
std::string artist = "";
std::string album = "";
std::string year = "";

//CommonTags commonTags;

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
		//std::cout << "LINE 55 Entry: " << entry.path().filename() << std::endl;
        if (isAudioFileSupported(getFileExtension(entry.path().filename())) == false) {
            continue;
        }
        else {
            if (entry.is_regular_file()) {
                TagLib::FileRef file(entry.path().c_str());

                if (!file.isNull() && file.tag()) {
                    //std::string artist = file.tag()->artist().to8Bit(true);

                    std::string album = file.tag()->album().to8Bit(true);
                    //std::cout << "LINE 61 Album: " << album << std::endl;
                    std::int16_t year = file.tag()->year();
                    //std::cout << "LINE 63 Year: " << year << std::endl;

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

                    std::cout << "Artist: " << artist << std::endl;


                    if (firstFile) {
                        commonArtist = artist;
                        commonAlbum = album;
                        commonYear = year;
						//std::cout << "LINE 91 Common Artist: '" << commonArtist << "'." << std::endl;
						//std::cout << "LINE 92 Common Album: '" << commonAlbum << "'." << std::endl;
						//std::cout << "LINE 93 Common Year: '" << commonYear << "'." << std::endl;
                        //keep firstFile as false if artist album and year are null
						if (artist.empty() && album.empty() && year == 0) {
							firstFile = true;
                        }
                        else {
                            firstFile = false;
                        }
                    }
                    else {
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

void updateTags(const std::string& filePath, const std::string& newArtist, const std::string& newAlbum) {
	TagLib::FileRef file(filePath.c_str());
	if (!file.isNull() && file.tag()) {
		TagLib::Tag* tag = file.tag();
		tag->setArtist(newArtist);
		tag->setAlbum(newAlbum);
		file.save();
	}
}

void updateTagsInDirectory(const std::string& directoryPath, const std::string& newArtist, const std::string& newAlbum) {
	for (const auto& entry : fs::directory_iterator(directoryPath)) {
		if (entry.is_regular_file()) {
			updateTags(entry.path().string(), newArtist, newAlbum);
		}
	}
}

void setCommonTags(const std::string& artist, const std::string& album, const std::string& year) {
	commonTags.artist = artist;
	commonTags.album = album;
	commonTags.year = year;
}

void findTheMostCommonTags(const std::string& directory) {
	std::vector<std::string> artists;
	std::vector<std::string> albums;
	std::vector<std::string> years;
	for (const auto& entry : fs::directory_iterator(directory)) {
		if (entry.is_regular_file()) {
			TagLib::FileRef file(entry.path().c_str());
			if (!file.isNull() && file.tag()) {
				std::cout << "Reading tags from " << entry.path().filename() << std::endl;
				std::cout << "Artist: " << file.tag()->artist().to8Bit(true) << std::endl;
				std::cout << "Album: " << file.tag()->album().to8Bit(true) << std::endl;
				std::cout << "Year: " << file.tag()->year() << std::endl;
				artists.push_back(file.tag()->artist().to8Bit(true));
				albums.push_back(file.tag()->album().to8Bit(true));
				years.push_back(std::to_string(file.tag()->year()));
			}
		}
	}
	std::string mostCommonArtist;
	std::string mostCommonAlbum;
	std::string mostCommonYear;
	int mostCommonArtistCount = 0;
	int mostCommonAlbumCount = 0;
	int mostCommonYearCount = 0;
	for (const auto& artist : artists) {
		int currentArtistCount = std::count(artists.begin(), artists.end(), artist);
		if (currentArtistCount > mostCommonArtistCount) {
			mostCommonArtist = artist;
			mostCommonArtistCount = currentArtistCount;
		}
	}
	for (const auto& album : albums) {
		int currentAlbumCount = std::count(albums.begin(), albums.end(), album);
		if (currentAlbumCount > mostCommonAlbumCount) {
			mostCommonAlbum = album;
			mostCommonAlbumCount = currentAlbumCount;
		}
	}
	for (const auto& year : years) {
		int currentYearCount = std::count(years.begin(), years.end(), year);
		if (currentYearCount > mostCommonYearCount) {
			mostCommonYear = year;
			mostCommonYearCount = currentYearCount;
		}
	}
	std::cout << "Most common artist: " << mostCommonArtist << std::endl;
	std::cout << "Most common album: " << mostCommonAlbum << std::endl;
	std::cout << "Most common year: " << mostCommonYear << std::endl;

	setCommonTags(mostCommonArtist, mostCommonAlbum, mostCommonYear);
}

std::vector<std::string> findFilesWithMatchingArtistAndAlbum(const std::string& directoryPath) {
	std::vector<std::string> matchingFiles;
	for (const auto& entry : fs::directory_iterator(directoryPath)) {
		if (entry.is_regular_file()) {
			TagLib::FileRef file(entry.path().c_str());
			if (!file.isNull() && file.tag()) {
				if (file.tag()->artist().to8Bit(true) == artist && file.tag()->album().to8Bit(true) == album) {
					matchingFiles.push_back(entry.path().string());
				}
			}
		}
	}
	return matchingFiles;
}