#include "naming-convention.h"
#include <string>
#include <vector>
#include <iostream>

std::string artistName = "";
std::string albumName = "";
std::string releaseYear = "";
std::vector<std::string> namingConventions = { "ArtistAlbumYear", "YearArtistAlbum", "ArtistAlbum" };
int selectedConvention = 0;
std::string namingConvention = "";


void setArtistName(const std::string name) {
	artistName = name;
}

void setAlbumName(const std::string name) {
	albumName = name;
}

void setReleaseYear(const std::string year) {
	releaseYear = year;
}

void listNamingConventions() {
	std::cout << "Select naming conventions. " << std::endl;
	int conventionCounter = 1;
	for (const auto& namingConvention : namingConventions) {
		std::cout << "[" << conventionCounter << "]" << namingConvention << std::endl;
		conventionCounter++;
	}
}



void setNamingConvention() {
	int input;
	listNamingConventions();
	std::cin >> input;
	
	//selectedConvention = input;
	switch (input) {
	case 1:
		namingConvention = namingConventions[0];
		break;
	case 2:
		namingConvention = namingConventions[1];
		break;
	case 3:
		namingConvention = namingConventions[2];
		break;
	default:
		std::cout << "Invalid selection. " << std::endl;
		break;
	}
}


void nameDirectory() {
	if (selectedConvention==0) {
		std::cout << "Please select a naming convention. " << std::endl;
		setNamingConvention();
	}
	switch (selectedConvention) {
	case 1:
		namingConvention = namingConventions[1];
		break;
	case 2:
		namingConvention = namingConventions[1];
		break;
	case 3:
		namingConvention = namingConventions[2];
		break;
	default:
		std::cout << "Invalid selection. " << std::endl;
		break;
	}
}

std::string generateAlbumDirectoryName(std::string artist, std::string album, std::string year) {
	std::string directoryName = "";
	if (namingConvention == "ArtistAlbumYear") {
		directoryName = "[" + artist + "]" + "-" + "[" + album + "]" + "-" + "[" + year + "]";
	}
	else if (namingConvention == "YearArtistAlbum") {
		directoryName = "[" + year + "]-[" + artist + "]-[" + album + "]";
	}
	else if (namingConvention == "ArtistAlbum") {
		directoryName = "[" + artist + "]-[" + album + "]";
	}
	else {
		std::cout << "Invalid naming convention. " << std::endl;
	}
	return directoryName;
}