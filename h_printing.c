/************** STRING PRINTING **************/


#include "shell.h"

/**
 * _print - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}
/**
 * _printe - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _printe(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _print_error - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print_error(int errorcode, program_data *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->command_execution_count, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->executable_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->tokenized_input[0]);
		if (errorcode == 2)
			_printe(": Illegal number: ");
		else
			_printe(": can't cd to ");
		_printe(data->tokenized_input[1]);
		_printe("\n");
	}
	else if (errorcode == 127)
	{
		_printe(data->executable_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->initial_command);
		_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printe(data->executable_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->initial_command);
		_printe(": Permission denied\n");
	}
	return (0);
}
