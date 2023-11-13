#include "shell.h"

/**
 * tokenize_input - Tokenizes the input string and stores it into an array.
 * @input_str: The input string to be parsed.
 * @delimiter: The delimiter to be used (a single character string).
 *
 * Returns: An array of tokens.
 */
char **tokenize_input(char *input_str, char *delimiter)
{
    int num_delimiters = 0;
    char **tokens = NULL;
    char *token = NULL;
    char *save_ptr = NULL;

    token = _strtok_r(input_str, delimiter, &save_ptr);

    while (token != NULL)
    {
        tokens = _realloc(tokens, sizeof(*tokens) * num_delimiters, sizeof(*tokens) * (num_delimiters + 1));
        tokens[num_delimiters] = token;
        token = _strtok_r(NULL, delimiter, &save_ptr);
        num_delimiters++;
    }

    tokens = _realloc(tokens, sizeof(*tokens) * num_delimiters, sizeof(*tokens) * (num_delimiters + 1));
    tokens[num_delimiters] = NULL;

    return tokens;
}

/**
 * print_string - Prints a string to the specified stream.
 * @string: The string to be printed.
 * @stream: The stream to print out to.
 *
 * Returns: void.
 */
void print_string(char *string, int stream)
{
    int i = 0;

    for (; string[i] != '\0'; i++)
        write(stream, &string[i], 1);
}

/**
 * remove_newline - Removes the newline character from a string.
 * @str: The string to be modified.
 *
 * Returns: void.
 */
void remove_newline(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '\n')
            break;
        i++;
    }
    str[i] = '\0';
}

/**
 * copy_string - Copies a string from source to destination.
 * @source: The source string.
 * @dest: The destination string.
 *
 * Returns: void.
 */
void copy_string(char *source, char *dest)
{
    int i = 0;

    for (; source[i] != '\0'; i++)
        dest[i] = source[i];
    dest[i] = '\0';
}

/**
 * get_string_length - Counts the length of a string.
 * @string: The string to be counted.
 *
 * Returns: The length of the string.
 */
int get_string_length(char *string)
{
    int length = 0;

    if (string == NULL)
        return length;
    
    for (; string[length] != '\0'; length++)
        ;
    return length;
}
