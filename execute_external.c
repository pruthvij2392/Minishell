#include "main.h"

// Function to read external commands from a file and store them in an array
void extract_external_commands(char **external_commands)
{
    // Open the file "external_commands.txt" in read mode
    FILE *fp = fopen("external_commands.txt", "r");
    if (!fp) // Check if the file opened successfully
    {
        perror("Failed to open command.txt"); // Print error message 
        exit(1); 
    }

    char word[100]; 
    int index = 0;  
    // Read words from the file until the end of file (EOF) is reached
    while (fscanf(fp, "%s", word) != EOF)
    {
        external_commands[index] = strdup(word); // Duplicate the word and store it in the array
        index++; // Move to the next position in the array
    }
    external_commands[index] = NULL; // Mark the end of the array with NULL

    fclose(fp); // Close the file
}

// Function to execute a pipeline of commands provided in the input string
void execute_external_commands(char *input_string)
{
    char *argv[20] = {NULL}; 
    char *cmds[10] = {NULL}; 
    int num_cmds = 0;        // Counter to track the number of commands

    // Split the input string into individual commands using "|" as the delimiter
    char *token = strtok(input_string, "|");
    while (token != NULL)
    {
        cmds[num_cmds++] = strdup(token); // Duplicate the command and store it in the cmds array
        token = strtok(NULL, "|");        // Get the next command
    }

    int pipes[num_cmds - 1][2]; 
    pid_t pids[num_cmds];       

    // Loop through each command to set up pipes and execute the commands
    for (int i = 0; i < num_cmds; i++)
    {
        // Create a pipe for all commands except the last one
        if (i < num_cmds - 1)
        {
            if (pipe(pipes[i]) == -1) // Create a pipe and check for errors
            {
                perror("pipe"); 
                exit(1);       // Exit the program
            }
        }

        // Fork a child process for each command
        pids[i] = fork();
        if (pids[i] == 0) // Child process
        {
            // Redirect input from the previous command (if not the first command)
            if (i > 0)
            {
                dup2(pipes[i - 1][0], STDIN_FILENO); // Redirect stdin to read from the previous pipe
            }
            // Redirect output to the next command (if not the last command)
            if (i < num_cmds - 1)
            {
                dup2(pipes[i][1], STDOUT_FILENO); // Redirect stdout to write to the next pipe
            }

            // Close all pipe ends in the child process to avoid resource leaks
            for (int j = 0; j < num_cmds - 1; j++)
            {
                close(pipes[j][0]); 
                close(pipes[j][1]); 
            }

            // Tokenize the command into arguments for execvp
            int arg_idx = 0;
            char *arg = strtok(cmds[i], " "); // Split the command into arguments using space as delimiter
            while (arg != NULL)
            {
                argv[arg_idx++] = arg; // Store each argument in the argv array
                arg = strtok(NULL, " "); // Get the next argument
            }
            argv[arg_idx] = NULL; // Mark the end of the argv array with NULL

            // Execute the command using execvp
            execvp(argv[0], argv);
            perror("execvp"); // Print error message if execvp fails
            exit(1);         // Exit the child process with an error code
        }
    }

    // Close all pipe ends in the parent process
    for (int i = 0; i < num_cmds - 1; i++)
    {
        close(pipes[i][0]); // Close read end of the pipe
        close(pipes[i][1]); // Close write end of the pipe
    }

    // Wait for all child processes to complete
    for (int i = 0; i < num_cmds; i++)
    {
        waitpid(pids[i], NULL, 0); // Wait for each child process to finish
    }
}