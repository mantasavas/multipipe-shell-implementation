#include "general.h"

// Command execution, fork process, create pipes...
void executeCommand(int commandNr, char *all_args[][MAX_ARGUMET]){
  int pid[commandNr];

  int totalPipes = (commandNr - 1) * 2;
  int pipes[totalPipes];

  // Initializing pipes
  for(int x = 0; x < totalPipes; x += 2)
    pipe(pipes + x);

  // Lets create as many processes as there are commands;
  // Each command executes in its own process
  for (int i = 0; i < commandNr; i++)
  {
    // For each command lets create a new process
    if ((pid[i] = fork()) < 0) 
    {
      // If failed to created new process inform user and quit
      printf("*** ERROR: forking child process failed\n");
      exit(-1);
    }
    else if (pid[i] == 0)
    {
      // If its child process

      // First process only produces result to pip write end,
      // as input it gets from stdin - console
      if(i == 0)
      {
        // setting (duplicating) process stdout to send output
        // to pipe write end (1)
        dup2(pipes[1], 1);
      
        // Closing all the other pipes ends, we don't need them
        for(int x = 0; x < totalPipes; x++)
          close(pipes[x]);

        // Execute program
        execvp(*all_args[i], all_args[i]);
        perror("Wrong Command Specified!");
        exit(1);

      // Last process only gets input from read pipe end end prints
      // to stdout - console
      }
      else if(i == commandNr - 1)
      {
        // setting (duplicating) process stdin to receive input
        // from pipes read end
        dup2(pipes[totalPipes - 2], 0);
        
        // Closing unsed pipe ends
        for(int x = 0; x < totalPipes; x++)
          close(pipes[x]);

        // Execute program
        execvp(*all_args[i], all_args[i]);
        perror("Wrong Command Specified!");
        exit(1);
      }
      // Middle process, receives input from pipe read end passes
      // to another process to write end of pipe
      else
      {
        // Let pipe "read end" go to process stdin
        dup2(pipes[i + (i - 2)], 0);
        // Let process stdout pass to pipe "write end" 
        dup2(pipes[i + i + 1], 1);
        
         // Closing unsed pipe ends
        for(int x = 0; x < totalPipes; x++)
          close(pipes[x]);
        
        // Execute program
        execvp(*all_args[i], all_args[i]);
        perror("Wrong Command Specified!");
        exit(1);
      }
    }
  }

  // In parent wait untill all process finished
  // Closing unsed pipe ends
  for(int x = 0; x < totalPipes; x++)
    close(pipes[x]);

  // Lets waite untill all proccesses finshed!
  for (int i = 0; i < commandNr; i++)
    waitpid(pid[i], NULL, 0);
}


// Convert types so that is could later be passed to execv function
void convertTypesForExecution(string commands[][MAX_ARGUMET], char *all_args[][MAX_ARGUMET])
{
  for(int x = 0; x < MAX_COMMAND; x++){
    if(commands[x][0] == "")
      break;

    for(int y = 0; y < MAX_ARGUMET; y++){
      // If empty string found, means no point of iterating further. end of arguments
      if (commands[x][y] == ""){
        all_args[x][y] = NULL;
        break;
      }
      
      all_args[x][y] = (char*) commands[x][y].c_str();
    }
  }
}


// Parsing user given input as string
int parseCommands(string parsedCommands[][MAX_ARGUMET], string commandString)
{
  // Command and its arguments numbers
  int commandNr = 0;
  int argumentNr = -1;
  

  // repeat for each pipe found
  for(unsigned int x = 0; x < commandString.size(); x++){
    
    if (commandString[x] != ' ')
      argumentNr++;

    string argument = "";
    
    // repeat for each space found
    while(commandString[x] != ' ' &&  x < commandString.size()){
      // if bar found, means next command, break and later save as whole command
      if(commandString[x] == '|')
        break;

      argument += commandString[x];
      x++;
    }

    if (argumentNr != -1 && argument != ""){
      parsedCommands[commandNr][argumentNr] = argument;
    }

    if(commandString[x] == '|'){
      argumentNr = -1;
      commandNr++;
    }
  }

  return commandNr + 1;
}
