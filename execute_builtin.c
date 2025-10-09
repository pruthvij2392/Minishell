#include "main.h"

extern int status; // External variable to store the status of the last command

// Function to execute internal (built-in) commands
void execute_internal_commands(char *input_string)
{
    if (strncmp(input_string, "exit", 4) == 0)
    {
	    printf(RED"Exiting minishell...\n"RESET);
	    exit(0);
    }

    if (strncmp(input_string, "pwd", 3) == 0)
    {
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
	    printf(CYAN "%s\n"RESET, cwd);
	}
	else
	{
	    perror(RED"ERROR: pwd failed"RESET);
	}
	   return;
    }

    if (strncmp(input_string, "echo", 4) == 0)  
    {
       echo(input_string, status);
        return;
     }


    if (strncmp(input_string, "cd ", 3) == 0)
    {
	   char *path = input_string + 3;
	    if (chdir(path) != 0)
	  {
	     perror(RED"ERROR: cd failed"RESET);
	  }
	   return;
    }

    printf(RED"%s: command not found\n"RESET, input_string);
}


// Function to handle echo commands
void echo(char *input_string, int status)
{
    if(!strcmp(input_string,"echo $?"))
    {
        printf(MAGENTA"%d\n"RESET, status);
    }
    else if(!strcmp(input_string,"echo $$"))
    {
        printf(MAGENTA"%d\n"RESET, getpid());
    }
    else if(!strcmp(input_string,"echo $SHELL"))
    {
        printf(MAGENTA"%s\n"RESET, getenv("SHELL"));
    }
    else  // other strings
    {
        printf(RED"%s\n"RESET, input_string + 5); // Skip "echo "
    }
}
