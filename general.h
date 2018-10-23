#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;


const int MAX_COMMAND = 10;
const int MAX_ARGUMET = 10;

void convertTypesForExecution(string commands[][MAX_ARGUMET], char *all_args[][MAX_ARGUMET]);
int parseCommands(string parsedCommands[][MAX_ARGUMET], string commandString);
void executeCommand(int commandNr, char *all_args[][MAX_ARGUMET]);
void parseCommand(char *line, char **argv);

#endif