#include "main.h"

extern char *external[200]; // External array to store external commands

// Function to check if a command is built-in or external
int check_command_type(char *command)
{
    // Array of built-in commands
    char *builtins[] = {
        "echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", 
        "let", "eval", "set", "unset", "export", "declare", "typeset", 
        "readonly", "getopts", "source", "exit", "exec", "shopt", "caller", 
        "true", "type", "hash", "bind", "help", NULL // NULL marks the end of the array
    };

    // Check if the command is a built-in command
    for (int i = 0; builtins[i]; i++) 
    {
        if (strcmp(builtins[i], command) == 0) // Compare the command with each built-in
        {
            return BUILTIN; // Return BUILTIN if a match is found
        }
    }

    // Check if the command is an external command
    for (int i = 0; external[i]; i++) // Loop through the external commands array
    {
        if (strcmp(external[i], command) == 0) // Compare the command with each external command
        {
            return EXTERNAL; // Return EXTERNAL if a match is found
        }
    }

    return NO_COMMAND; // Return NO_COMMAND if the command is neither built-in nor external
}

// Function to extract the command from the input string
char *get_command(char *input_string)
{
    char *cmd = malloc(20); // Allocate memory for the command (max 20 characters)
    int i;

    // Extract the command from the input string (stop at the first space or end of string)
    for (i = 0; input_string[i] && input_string[i] != ' '; i++)
    {
        cmd[i] = input_string[i]; // Copy each character to the cmd buffer
    }
    cmd[i] = '\0'; // Null-terminate the command string

    return cmd; // Return the extracted command
}







// Use the global external_commands array
//static char *external_commands[MAX_EXTERNAL_CMDS] = {NULL};  // Static to persist


// int check_command_type(char *command)
//  {
//     // Check if the command matches a built-in command
//     char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd",
//         "dirs", "let", "eval", "set", "unset", "export", "declare",
//         "typeset", "readonly", "getopts", "source", "exit", "exec",
//         "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};
    
//     //  if(strlen(command)== 0) {   // Handle null or empty input as NO_COMMAND
//     //    return NO_COMMAND;
//     //   }

//     //  // CHECK THE COMMAND IS BUILTIN 
//     //  for(int i=0;builtins[i] != NULL ; i++)
//     //  {
//     //     if(strcmp(command , builtins[i]) == 0)
//     //     {
//     //         return BUILTIN ;
//     //     }
//     //  } 

//     // // Extract external commands from file
//     // static char *external_commands[MAX_EXTERNAL_CMDS] = {NULL}; // Static to persist across calls
//     // if (external_commands[0] == NULL) {
//     // extract_external_commands(external_commands);
//     // }


