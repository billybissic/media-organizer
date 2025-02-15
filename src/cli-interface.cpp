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
   std::cout << "Commands:\n";
   std::cout << "  help           - Show help\n";
   std::cout << "  exit           - Exits the application\n";
   std::cout << "  sort-albums    - Sort albums\n";
   std::cout << "   required: \n";
   std::cout << "     --sort-directory \n";
   std::cout << "     --destination \n";
   std::cout << "   optional: \n";
   std::cout << "     --dry-run\n";
   std::cout << "  sort-tracks    - Sort tracks\n";
   std::cout << "   required: \n";
   std::cout << "     --sort-directory \n";
   std::cout << "     --destination \n";
   std::cout << "   optional: \n";
   std::cout << "     --dry-run\n";
   std::cout << "  sort-directory - Sort directory\n";
   std::cout << "   required: \n";
   std::cout << "     --sort-directory \n";
   std::cout << "     --destination \n";
   std::cout << "   optional: \n";
   std::cout << "     --dry-run\n";
   std::cout << "  start-daemon   - Start daemon\n";
   std::cout << "   required: \n";
   std::cout << "     --sort-directory \n";
   std::cout << "     --destination \n";
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
        std::cout << "Exiting application...\n";
        exit(0);
    }

    // Required arguments check
    if (args.find("--sort-directory") == args.end() || args.find("--destination") == args.end()) {
        std::cerr << "Error: Missing required arguments: --sort-directory and --destination\n";
        return;
    }

    std::string sortDirectory = args.at("--sort-directory");
    std::string destination = args.at("--destination");
    bool dryRun = args.find("--dry-run") != args.end();

    if (!checkIfDirectoryExists(sortDirectory)) {
        std::cerr << "Error: Sort directory does not exist: " << sortDirectory << "\n";
        return;
    }

    if (command == "sort-albums" || command == "sort-tracks" || command == "sort-directory") {
        std::cout << "Sorting" << std::endl << "From: " << sortDirectory << std::endl << "To: " << destination << std::endl;
        if (dryRun) {
            setDryRun(true);
            std::cout << "[DRY RUN] No files will be moved.\n";
        }
        else {
            std::cout << "Files will be moved.\n";
        }

        std::cout << "Would you like to continue? [y/n]: ";
        std::string response;
        std::cin >> response;
        if (response != "y") {
            std::cout << "Exiting...\n";
            return;
        }
        else {
			std::cout << "Continuing...\n";
			clearScreen();
            sortDirectoryOfAlbums(sortDirectory, destination);
            //getFilesInDirectory(sortDirectory);
        }
		 
        
    } else if (command == "start-daemon") {
		setDaemonStarted(true);
        std::cout << "Starting daemon for " << sortDirectory << " with destination " << destination << "\n";
    } else {
        std::cerr << "Error: Unknown command: " << command << "\n";
    }
}

