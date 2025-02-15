//include/cli-commands.h
#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include <string>
#include <map>

extern bool isDryRun;
extern bool isDaemonStarted;

std::map<std::string, std::string> parseArguments(int argc, char* argv[]);

void executeCommand(const std::string& command, const std::map<std::string, std::string>& args);
void sortAlbums(); // sorts albums
void sortTracks(); // sorts files only
void sortDirectory(); // sorts albums then sorts tracks
void startDaemon(); //starts daemon process and watches directory for changes.
void dryRun(); // sets flag for dry run
void printHelp(); // shows the commands for the cli
 
#endif
