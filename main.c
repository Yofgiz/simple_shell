#include "shell.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	program_data data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	initialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	command_loop(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_data - initialize_data the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void initialize_data(program_data *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->executable_name = argv[0];
	data->user_input = NULL;
	data->initial_command = NULL;
	data->command_execution_count = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->input_file_descriptor = STDIN_FILENO;
	else
	{
		data->input_file_descriptor = open(argv[1], O_RDONLY);
		if (data->input_file_descriptor == -1)
		{
			_printe(data->executable_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokenized_input = NULL;
	data->environment_variables = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->environment_variables[i] = str_duplicate(env[i]);
		}
	}
	data->environment_variables[i] = NULL;
	env = data->environment_variables;

	data->alias_pointers = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_pointers[i] = NULL;
	}
}
/**
 * command_loop - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void command_loop(char *prompt, program_data *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->command_execution_count))
	{
		_print(prompt);
		error_code = string_len = read_input_line(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			parse_and_replace_alias(data);
			parse_and_replace_variables(data);
			tokenize(data);
			if (data->tokenized_input[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
