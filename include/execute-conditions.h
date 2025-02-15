// including/execute-conditions.h
#ifndef EXECUTE_CONDITIONS_H
#define EXECUTE_CONDITIONS_H

#include <string>
#include <iostream>

extern bool isDryRun;
extern bool isDaemonStarted;

void setDryRun(bool dryRun);
void setDaemonStarted(bool daemonStarted);
void clearScreen();


#endif
