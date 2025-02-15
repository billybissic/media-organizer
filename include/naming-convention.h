// include/naming-convention.h
#ifndef NAMING_CONVENTION_H
#define NAMING_CONVENTION_H

#include <string>
#include <vector>
#include <iostream>

extern std::string artistName;
extern std::string releaseYear;
extern std::string albumName;
extern std::vector<std::string> namingConventions;
extern int selectedConvention;

void setArtistName(const std::string& name);
void setReleaseYear(const std::string& year);
void setAlbumName(const std::string& name);
void setNamingConvention();
void listNamingConventions();
void nameDirectory();
std::string generateAlbumDirectoryName(const std::string artist, const std::string album, const std::string year);

#endif