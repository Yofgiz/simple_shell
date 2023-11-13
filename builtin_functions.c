#include "shell.h"

char **custom_environment;  // Custom environment variable array

/**
 * print_environment - Prints the current environment variables.
 * @tokenized_command: The command entered.
 *
 * This function iterates over the custom_environment array
 * and prints each environment variable to the standard output.
 *
 * Returns: void
 */
void print_environment(char **tokenized_command __attribute__((unused)))
{
    int i;

    for (i = 0; custom_environment[i] != NULL; i++)
    {
        print(custom_environment[i], STDOUT_FILENO);
        print("\n", STDOUT_FILENO);
    }
}

/**
 * shell_exit - Exits the shell.
 * @tokenized_command: The command entered.
 *
 * This function is responsible for handling the exit command.
 * If the command is called without any arguments, it will exit
 * the shell with the current status. If an argument is provided,
 * it will attempt to convert it to an integer and exit the shell
 * with the specified exit code. If the argument is not a valid
 * integer, an error message will be printed.
 *
 * Returns: void
 */
void shell_exit(char **tokenized_command)
{
    int num_tokens = 0, exit_code;

    for (; tokenized_command[num_tokens] != NULL; num_tokens++)
        ;

    if (num_tokens == 1)
    {
        free(tokenized_command);
        free(line);
        free(commands);
        exit(status);
    }
    else if (num_tokens == 2)
    {
        exit_code = _atoi(tokenized_command[1]);
        if (exit_code == -1)
        {
            print(shell_name, STDERR_FILENO);
            print(": 1: exit: you can not use this number: ", STDERR_FILENO);
            print(tokenized_command[1], STDERR_FILENO);
            print("\n", STDERR_FILENO);
            status = 2;
        }
        else
        {
            free(line);
            free(tokenized_command);
            free(commands);
            exit(exit_code);
        }
    }
    else
    {
        print("$: exit takes only one argument\n", STDERR_FILENO);
    }
}
