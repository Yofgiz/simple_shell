/************** ALIAS HANDLING **************/


#include "shell.h"

/**
 * print_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int print_alias(program_data *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_pointers)
	{
		alias_length = str_length(alias);
		for (i = 0; data->alias_pointers[i]; i++)
		{
			if (!alias || (str_compare(data->alias_pointers[i], alias, alias_length)
				&&	data->alias_pointers[i][alias_length] == '='))
			{
				for (j = 0; data->alias_pointers[i][j]; j++)
				{
					buffer[j] = data->alias_pointers[i][j];
					if (data->alias_pointers[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				append_to_buffer(buffer, "'");
				append_to_buffer(buffer, data->alias_pointers[i] + j + 1);
				append_to_buffer(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(program_data *data, char *name)
{
	int i, alias_length;

	/* validate the arguments */
	if (name == NULL || data->alias_pointers == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_pointers[i]; i++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_compare(name, data->alias_pointers[i], alias_length) &&
			data->alias_pointers[i][alias_length] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_pointers[i] + alias_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, program_data *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_pointers == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* search if the value of the alias is another alias */
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (j = 0; data->alias_pointers[j]; j++)
		if (str_compare(buffer, data->alias_pointers[j], i) &&
			data->alias_pointers[j][i] == '=')
		{/* if the alias alredy exist */
			free(data->alias_pointers[j]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		append_to_buffer(buffer, "=");
		append_to_buffer(buffer, temp);
		data->alias_pointers[j] = str_duplicate(buffer);
	}
	else /* if the alias does not exist */
		data->alias_pointers[j] = str_duplicate(alias_string);
	return (0);
}
