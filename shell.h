#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* DATA STRUCTURES **************/

/**
 * struct info - A struct for the program's data.
 * @executable_name: a pointer to a string representing the name of the executable program.
 * @user_input: a pointer to a string containing the input read by the read_input_line function
 * @initial_command: a pointer to a string that holds the name of the first command typed by the user.
 * @command_execution_count: a integer representing the count of executed commands. 
 * @input_file_descriptor:  an integer representing a file descriptor associated with the input of commands.
 * @tokenized_input: a pointer to an array of strings that holds tokenized input.
 * @environment_variables: a pointer to an array of strings that represents a copy of the environment variables associated with the program.
 * @alias_pointers: a pointer to an array of strings that holds pointers to aliases.
 */
typedef struct info
{
	char *executable_name;
	char *user_input;
	char *initial_command;
	int command_execution_count;
	int input_file_descriptor;
	char **tokenized_input;
	char **environment_variables;
	char **alias_pointers;
} program_data;

/**
 * struct builtins - A struct for the builtins.
 * @builtin: a pointer to a string representing the name of a built-in command.
 * @function: a function pointer that points to a function associated with the specific built-in command.
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(program_data *data);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  main.c  ========*/

/* Initialize the struct with the info of the program */
void initialize_data(program_data *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void command_loop(char *prompt, program_data *data);

/* Print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  read_input_line.c  ========*/

/* Read one line of the standard input*/
int read_input_line(program_data *data);

/* Split each line for the logical operators if it exist */
int handle_logical_operators(char *array_commands[], int i, char array_operators[]);


/*======== parse_replace.c ========*/

/* Parse and replace variables */
void parse_and_replace_variables(program_data *data);

/* Parse and replace aliases */
void parse_and_replace_alias(program_data *data);

/* Append the string to the end of the buffer*/
int append_to_buffer(char *buffer, char *str_to_add);


/*======== others_1.c ========*/

/* Separate the string in tokens using a designed delimiter */
void tokenize(program_data *data);

/* Extract tokens from strings */
char *_strtok(char *line, char *delim);

/* Execute a command with its entire path */
int execute(program_data *data);


/*======== others_2.c ========*/

/* Creates an array of the path directories */
char **tokenize_path(program_data *data);

/* Search for program in path */
int find_program(program_data *data);

/* If match a builtin, executes it */
int builtins_list(program_data *data);


/************** BUILTINS **************/


/*======== b_more.c ========*/

/* Close the shell */
int builtin_exit(program_data *data);

/* Change the current directory */
int builtin_cd(program_data *data);

/* Set the work directory */
int set_work_directory(program_data *data, char *new_dir);

/* Show help information */
int builtin_help(program_data *data);

/* Set, unset and show alias */
int builtin_alias(program_data *data);


/*======== b_env.c ========*/

/* Shows the environment where the shell runs */
int builtin_env(program_data *data);

/* create or override a variable of environment */
int builtin_set_env(program_data *data);

/* delete a variable of environment */
int builtin_unset_env(program_data *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== h_env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, program_data *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, program_data *data);

/* Remove a key from the environment */
int env_remove_key(char *key, program_data *data);

/* prints the current environ */
void print_environ(program_data *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== h_memory_management.c ========*/

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(program_data *data);

/* Free all field of the data */
void free_all_data(program_data *data);



/************** HELPERS FOR PRINTING **************/


/*======== h_printing.c ========*/

/* Prints a string in the standar output */
int _print(char *string);

/* Prints a string in the standar error */
int _printe(char *string);

/* Prints a string in the standar error */
int _print_error(int errorcode, program_data *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== h_string.c ========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);


/*======== h_numbers.c ========*/

/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);


/************** ALIAS HANDLING **************/

/*======== handle_alias.c ========*/

/* print the list of alias */
int print_alias(program_data *data, char *alias);

/* get the alias name */
char *get_alias(program_data *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, program_data *data);


#endif
