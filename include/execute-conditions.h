// including/execute-conditions.h
#ifndef EXECUTE_CONDITIONS_H
#define EXECUTE_CONDITIONS_H

#include <string>
#include <iostream>

extern bool isDryRun;
extern bool isDaemonStarted;
extern bool allowCompilations;

void setDryRun(bool dryRun);
void setAllowCompilations(bool allow);
void setDaemonStarted(bool daemonStarted);
void clearScreen();


#endif
