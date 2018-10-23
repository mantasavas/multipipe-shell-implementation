#include "general.h"

/*
  ps -a | grep o | grep gsd | cut -b 1-5
  ps aux | grep root | cut -b 1-10
  cat scores | grep Villanova | cut -b 1-10
  ls -a | grep e
*/

int main() {
  string line;                                  
  
  while (true) {
    string commands[MAX_COMMAND][MAX_ARGUMET];

    // Prompt user to enter commands
    printf("Shell -> ");    
    getline(cin, line);

    // Quit shell program if these inputs given
    if (line == "exit" || cin.eof()){
      cout << endl;
      exit(1);
    // If enter pressed, don't pass for execution 
    }else if(line == "\0"){
      continue;
    }

    // Parse all commands seperated by pipes
    int commandNr = parseCommands(commands, line);

    // Convert types and prepare for execuction
    char *all_args[MAX_COMMAND][MAX_ARGUMET];
    convertTypesForExecution(commands, all_args);

    // Execute commands
    executeCommand(commandNr, all_args);
  }
  return 1;
}