#include "cli-interface.h"
#include "execute-conditions.h"
#include "music-sort.h"
#include "directory.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

void printHelp() {
   std::cout << "Commands:"                                     << std::endl;
   std::cout << "  help           - Show help"                  << std::endl;
   std::cout << "  exit           - Exits the application"      << std::endl;
   std::cout << "  sort-albums    - Sort albums"                << std::endl;
   std::cout << "   required: "                                 << std::endl;
   std::cout << "     --sort-directory "                        << std::endl;
   std::cout << "     --destination "                           << std::endl;
   std::cout << "   optional: "                                 << std::endl;
   std::cout << "     --dry-run"                                << std::endl;
   std::cout << "  sort-tracks    - Sort tracks"                << std::endl;
   std::cout << "   required: "                                 << std::endl;
   std::cout << "     --sort-directory "                        << std::endl;
   std::cout << "     --destination "                           << std::endl;
   std::cout << "   optional: "                                 << std::endl;
   std::cout << "     --dry-run"                                << std::endl;
   std::cout << "  sort-directory - Sort directory"             << std::endl;
   std::cout << "   required: "                                 << std::endl;
   std::cout << "     --sort-directory "                        << std::endl;
   std::cout << "     --destination "                           << std::endl;
   std::cout << "   optional: "                                 << std::endl;
   std::cout << "     --dry-run"                                << std::endl;
   std::cout << "  start-daemon   - Start daemon"               << std::endl;
   std::cout << "   required: "                                 << std::endl;
   std::cout << "     --sort-directory "                        << std::endl;
   std::cout << "     --destination "                           << std::endl;
}

std::map<std::string, std::string> parseArguments(int argc, char* argv[]) {
    std::map<std::string, std::string> args;
    for (int i = 2; i < argc; i += 2) {
        if (i + 1 < argc) {
            args[argv[i]] = argv[i + 1];
        }
    }
    return args;
}

void executeCommand(const std::string& command, const std::map<std::string, std::string>& args) {
    if (command == "help") {
        printHelp();
        return;
    }

    if (command == "exit") {
        std::cout << "Exiting application..." << std::endl;
        exit(0);
    }

    // Required arguments check
    if (args.find("--sort-directory") == args.end() || args.find("--destination") == args.end()) {
        std::cerr << "Error: Missing required arguments: --sort-directory and --destination" << std::endl;
        return;
    }

    std::string sortDirectory = args.at("--sort-directory");
    std::string destination = args.at("--destination");
    bool dryRun = args.find("--dry-run") != args.end();

    if (!checkIfDirectoryExists(sortDirectory)) {
        std::cerr << "Error: Sort directory does not exist: " << sortDirectory << std::endl;
        return;
    }

    if (command == "sort-albums" || command == "sort-tracks" || command == "sort-directory") {
        std::cout << "Sorting" << std::endl << "From: " << sortDirectory << std::endl << "To: " << destination << std::endl;
        if (dryRun) {
            setDryRun(true);
            std::cout << "[DRY RUN] No files will be moved." << std::endl;
        }
        else {
            std::cout << "Files will be moved." << std::endl;
        }

        std::cout << "Would you like to continue? [y/n]: ";
        std::string response;
        std::cin >> response;
        if (response != "y") {
            std::cout << "Exiting..." << std::endl;
            return;
        }
        else {
			std::cout << "Continuing..." << std::endl;
			clearScreen();
            sortDirectoryOfAlbums(sortDirectory, destination);
            //getFilesInDirectory(sortDirectory);
        }
		 
        
    } else if (command == "start-daemon") {
		setDaemonStarted(true);
        std::cout << "Starting daemon for " << sortDirectory << " with destination " << destination << std::endl;
    } else {
        std::cerr << "Error: Unknown command: " << command << std::endl;
    }
}

