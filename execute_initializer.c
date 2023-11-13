#include "shell.h"

/**
 * execute_initializer - Starts executing the command.
 * @command: The current command to be executed.
 * @command_type: The type of command to be parsed.
 *
 * Returns: Void.
 */
void execute_initializer(char **command, int command_type)
{
    pid_t process_id;

    if (command_type == EXTERNAL_COMMAND || command_type == PATH_COMMAND)
    {
        process_id = fork();
        if (process_id == 0)
            execute_command(command, command_type);
        else
        {
            waitpid(process_id, &status, 0);
            status >>= 8;
        }
    }
    else
        execute_command(command, command_type);
}
