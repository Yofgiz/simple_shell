/************** BUILTINS ENVIRONMENT **************/


#include "shell.h"

/**
 * builtin_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_env(program_data *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* if not arguments */
	if (data->tokenized_input[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->tokenized_input[1][i]; i++)
		{/* checks if exists a char = */
			if (data->tokenized_input[1][i] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_set_key(cpname, data->tokenized_input[1] + i + 1, data);

				/* print the environ */
				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{/* print the variable if it does not exist in the environ */
					_print(data->tokenized_input[1]);
					_print("\n");
				}
				else
				{/* returns the old value of the var*/
					env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokenized_input[1][i];
		}
		errno = 2;
		perror(data->initial_command);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_set_env(program_data *data)
{
	/* validate args */
	if (data->tokenized_input[1] == NULL || data->tokenized_input[2] == NULL)
		return (0);
	if (data->tokenized_input[3] != NULL)
	{
		errno = E2BIG;
		perror(data->initial_command);
		return (5);
	}

	env_set_key(data->tokenized_input[1], data->tokenized_input[2], data);

	return (0);
}

/**
 * builtin_unset_env - ..
 * @data: struct for the program's data'
 * Return: ..
 */
int builtin_unset_env(program_data *data)
{
	/* validate args */
	if (data->tokenized_input[1] == NULL)
		return (0);
	if (data->tokenized_input[2] != NULL)
	{
		errno = E2BIG;
		perror(data->initial_command);
		return (5);
	}
	env_remove_key(data->tokenized_input[1], data);

	return (0);
}
