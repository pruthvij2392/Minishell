/* Name : pruthvi jyoti
 ID : 24018_018
 Date: 21/02/24
*/
#include "main.h"

// Global variables
pid_t pid;              // Process ID for forking
int status;             // Status of child processes
char *external[200];    // Array to store external commands

// Main function
int main()
{
    char input_string[100]; // Buffer to store user input
    char prompt[100] = "Minishell_PJ$:"; // Default shell prompt
    system("clear"); // Clear screen
    scan_input(prompt, input_string); // Start the shell input loop
    return 0; // Exit the program
}

// Function to handle shell input and command execution
void scan_input(char *prompt, char *input_string)
{
    extract_external_commands(external); // Load external commands from a file

    while (1) 
    {
        // Print the shell prompt
        printf(GREEN "%s " RESET, prompt);
        fflush(stdout); // Flush the output buffer to ensure the prompt is displayed

        // Read user input
        if (fgets(input_string, 100, stdin) == NULL)
        {
            printf(RED "Error reading input\n" RESET); 
            continue; 
        }

        // Remove the newline character from the input
        input_string[strcspn(input_string, "\n")] = '\0';

        // Skip empty input
        if (strlen(input_string) == 0)
        {
            continue;  // Skip to the next iteration
        }

        // Check if the input changes the prompt
        copy_change(prompt, input_string);

        // Skip if the input is a prompt change command (PSI=)
        if (strncmp(input_string, "PS1=", 4) == 0)
        {
            continue; 
        }

        // Extract the command from the input string
        char *cmd = get_command(input_string);

        // Check if the command is built-in or external
        int ret = check_command_type(cmd);

        if (ret == BUILTIN) // Built-in command
         {
             printf(YELLOW "Executing Builtin command: %s\n" RESET, cmd);
             execute_internal_commands(input_string);  // Now calling built-in command function
              return ;
         }
        else if (ret == EXTERNAL) // External command
        {
            printf(YELLOW "Executing external command: %s\n" RESET, cmd);
            int pid = fork(); // Fork a child process

            if (pid == 0) // Child process
            {
                execlp(cmd, cmd, NULL); // Execute the command
                perror(RED "ERROR: Execution failed" RESET); // Print error if execution fails
                exit(EXIT_FAILURE); // Exit the child process with failure status
            }
            else if (pid > 0) // Parent process
            {
                int status;
                waitpid(pid, &status, WUNTRACED); // Wait for the child process to complete
            }
            else // Fork failed
            {
                perror(RED "ERROR: Fork failed" RESET); // Print error if fork fails
            }
        }
        else // Command not found
        {
            printf(RED "%s: command not found\n" RESET, cmd);
        }

        free(cmd); // Free the memory allocated for the command
    }
}

// Signal handler for handling interrupts (e.g., Ctrl+C)
void signal_handler(int sig_num)
{
    printf("\n"); // Print a newline
    printf(GREEN "Minishell$ " RESET); // Reprint the prompt
    fflush(stdout); // Flush the output buffer
}

// Function to change the shell prompt based on user input
void copy_change(char *prompt, char *input_string)
{
    // Check if the input is a prompt change command (PSI=)
    if (strncmp(input_string, "PS1=", 4) == 0 && input_string[4] != ' ')
    {
        strcpy(prompt, input_string + 4); // Update the prompt
    }
}