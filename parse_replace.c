#include "shell.h"

/**
 * parse_and_replace_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void parse_and_replace_variables(program_data *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->user_input == NULL)
		return;
	append_to_buffer(line, data->user_input);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_to_string(errno, expansion, 10);
			append_to_buffer(line, expansion);
			append_to_buffer(line, data->user_input + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			append_to_buffer(line, expansion);
			append_to_buffer(line, data->user_input + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = env_get_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			append_to_buffer(expansion, line + i + j);
			temp ? append_to_buffer(line, temp) : 1;
			append_to_buffer(line, expansion);
		}
	if (!str_compare(data->user_input, line, 0))
	{
		free(data->user_input);
		data->user_input = str_duplicate(line);
	}
}

/**
 * parse_and_replace_alias - expand aliases
 * @data: a pointer to a struct containing the program's data
 *
 * Return: nothing, but sets errno.
 */
void parse_and_replace_alias(program_data *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->user_input == NULL)
		return;

	append_to_buffer(line, data->user_input);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			append_to_buffer(expansion, line + i + j);
			line[i] = '\0';
			append_to_buffer(line, temp);
			line[str_length(line)] = '\0';
			append_to_buffer(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->user_input);
		data->user_input = str_duplicate(line);
	}
}

/**
 * append_to_buffer - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int append_to_buffer(char *buffer, char *str_to_add)
{
	int length, i;

	length = str_length(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
