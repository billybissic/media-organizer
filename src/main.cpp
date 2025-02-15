#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "cli-interface.h"

int main(int argc, char* argv[]) {
   if (argc < 2) {
      std::cerr << "Error: No command provided.\n";
      printHelp();
      return EXIT_FAILURE;
   }

   std::string command = argv[1];
   std::map<std::string, std::string> args = parseArguments(argc, argv);
   executeCommand(command, args);

   return 0;
}
