#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
 

#define BUILTIN 1
#define EXTERNAL 2
#define NO_COMMAND 3
#define UNKNOWN_COMMAND 4

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"


/*
void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string);

void copy_change(char *prompt, char *input_string);

int check_command_type(char *command);
void echo(char *input_string, int status);
void execute_internal_commands(char *input_string);
void signal_handler(int sig_num);
void extract_external_commands(char **external_commands);
*/

// main.h


#define MAX_INPUT_SIZE 100
#define MAX_CMD_SIZE 25
#define MAX_EXTERNAL_CMDS 155  // Move this here!


void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string);
void extract_external_commands(char **external_commands) ;
void execute_external_commands(char *input_string) ;
int check_command_type(char *command);
void execute_internal_commands(char *input_string);




void echo(char *input_string, int status) ;
void clear_screen();
void print_prompt();
void signal_handler(int sig_num);

void update_prompt(char *input);
void copy_change(char *prompt, char *input_string) ;




#endif
