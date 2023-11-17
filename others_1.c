#include "shell.h"

/**
 * tokenize - This function separate the string using a designed delimiter.
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(program_data *data)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	length = str_length(data->user_input);
	if (length)
	{
		if (data->user_input[length - 1] == '\n')
			data->user_input[length - 1] = '\0';
	}

	for (i = 0; data->user_input[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->user_input[i] == delimiter[j])
				counter++;
		}
	}

	data->tokenized_input = malloc(counter * sizeof(char *));
	if (data->tokenized_input == NULL)
	{
		perror(data->executable_name);
		exit(errno);
	}
	i = 0;
	data->tokenized_input[i] = str_duplicate(
			_strtok(data->user_input, delimiter));
	data->initial_command = str_duplicate(data->tokenized_input[0]);
	while (data->tokenized_input[i++])
	{
		data->tokenized_input[i] = str_duplicate(_strtok(NULL, delimiter));
	}
}


/**
 * _strtok - separates strings with delimiters
 * @line: It´s pointer to array we receive in getline.
 * @delim: It´s characters we mark off string in parts.
 * Return: A pointer to the created token
*/
char *_strtok(char *line, char *delim)
{
	int j;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			break;
		}
		if (delim[j] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}

/**
 * execute - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If sucess returns zero, otherwise, return -1.
 */
int execute(program_data *data)
{
	int retval = 0, status;
	pid_t pidd;

	retval = builtins_list(data);
	if (retval != -1)
		return (retval);

	retval = find_program(data);
	if (retval)
	{
		return (retval);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->initial_command);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			retval = execve(data->tokenized_input[0],
					data->tokenized_input, data->environment_variables);
			if (retval == -1)
				perror(data->initial_command), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}

