/************** MEMORY MANAGEMENT **************/


#include "shell.h"

/**
 * free_recurrent_data - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_recurrent_data(program_data *data)
{
	if (data->tokenized_input)
		free_array_of_pointers(data->tokenized_input);
	if (data->user_input)
		free(data->user_input);
	if (data->initial_command)
		free(data->initial_command);

	data->user_input = NULL;
	data->initial_command = NULL;
	data->tokenized_input = NULL;
}

/**
 * free_all_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_all_data(program_data *data)
{
	if (data->input_file_descriptor != 0)
	{
		if (close(data->input_file_descriptor))
			perror(data->executable_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->environment_variables);
	free_array_of_pointers(data->alias_pointers);
}

/**
 * free_array_of_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
