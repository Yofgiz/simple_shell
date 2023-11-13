#include "shell.h"

/**
 * tokenize_string - Tokenizes a string.
 * @string: The string to be tokenized.
 * @delim: The delimiter to be used to tokenize the string.
 * @save_ptr: Pointer to be used to keep track of the next token.
 *
 * Returns: The next available token.
 */
char *tokenize_string(char *string, char *delim, char **save_ptr)
{
    char *finish;

    if (string == NULL)
        string = *save_ptr;

    if (*string == '\0')
    {
        *save_ptr = string;
        return (NULL);
    }

    string += get_prefix_length(string, delim);
    if (*string == '\0')
    {
        *save_ptr = string;
        return (NULL);
    }

    finish = string + get_segment_length(string, delim);
    if (*finish == '\0')
    {
        *save_ptr = finish;
        return (string);
    }

    *finish = '\0';
    *save_ptr = finish + 1;
    return (string);
}

/**
 * string_to_integer - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Returns: The converted integer.
 */
int string_to_integer(char *s)
{
    unsigned int num = 0;

    do {
        if (*s == '-')
            return (-1);
        else if ((*s < '0' || *s > '9') && *s != '\0')
            return (-1);
        else if (*s >= '0' && *s <= '9')
            num = (num * 10) + (*s - '0');
        else if (num > 0)
            break;
    } while (*s++);
    return (num);
}

/**
 * reallocate_memory - Reallocates a memory block.
 * @ptr: Pointer to the memory previously allocated with a call to malloc.
 * @old_size: Size of ptr.
 * @new_size: Size of the new memory to be allocated.
 *
 * Returns: Pointer to the address of the new memory block.
 */
void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *temp_block;
    unsigned int i;

    if (ptr == NULL)
    {
        temp_block = malloc(new_size);
        return (temp_block);
    }
    else if (new_size == old_size)
        return (ptr);
    else if (new_size == 0 && ptr != NULL)
    {
        free(ptr);
        return (NULL);
    }
    else
    {
        temp_block = malloc(new_size);
        if (temp_block != NULL)
        {
            for (i = 0; i < min(old_size, new_size); i++)
                *((char *)temp_block + i) = *((char *)ptr + i);
            free(ptr);
            return (temp_block);
        }
        else
            return (NULL);
    }
}

/**
 * handle_ctrl_c - Handles the signal raised by CTRL-C.
 * @signum: Signal number.
 *
 * Returns: Void.
 */
void handle_ctrl_c(int signum)
{
    if (signum == SIGINT)
        print("\n($) ", STDIN_FILENO);
}

/**
 * remove_comments - Removes/ignores everything after a '#' character.
 * @input: Input to be used.
 *
 * Returns: Void.
 */
void remove_comments(char *input)
{
    int i = 0;

    if (input[i] == '#')
        input[i] = '\0';
    while (input[i] != '\0')
    {
        if (input[i] == '#' && input[i - 1] == ' ')
            break;
        i++;
    }
    input[i] = '\0';
}
