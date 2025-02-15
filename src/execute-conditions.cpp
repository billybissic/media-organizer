#include "execute-conditions.h"
#include <string>
#include <iostream>

bool isDryRun = false;
bool isDaemonStarted = false;

void setDryRun(bool dryRun) {
	isDryRun = dryRun;
}

void setDaemonStarted(bool daemonStarted) {
	isDaemonStarted = daemonStarted;
}

void clearScreen() {
	std::cout << "\033[2J\033[H"; // ANSI escape code: clears screen and moves cursor to top
}