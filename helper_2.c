#include "shell.h"

/**
 * compare_strings - Compares two strings.
 * @str1: The first string to be compared.
 * @str2: The second string to be compared.
 *
 * Returns: The difference between the two strings.
 */
int compare_strings(char *str1, char *str2)
{
    int i = 0;

    while (str1[i] != '\0')
    {
        if (str1[i] != str2[i])
            break;
        i++;
    }
    return (str1[i] - str2[i]);
}

/**
 * concatenate_strings - Concatenates two strings.
 * @destination: The string to be concatenated to.
 * @source: The string to be concatenated.
 *
 * Returns: The address of the new concatenated string.
 */
char *concatenate_strings(char *destination, char *source)
{
    char *new_string = NULL;
    int dest_length = get_string_length(destination);
    int source_length = get_string_length(source);

    new_string = malloc(sizeof(*new_string) * (dest_length + source_length + 1));
    copy_string(destination, new_string);
    copy_string(source, new_string + dest_length);
    new_string[dest_length + source_length] = '\0';
    return (new_string);
}

/**
 * get_prefix_length - Gets the length of a prefix substring.
 * @str1: The string to be searched.
 * @str2: The string to be used.
 *
 * Returns: The number of bytes in the initial segment of str1 which are part of str2.
 */
int get_prefix_length(char *str1, char *str2)
{
    int i = 0;
    int match = 0;

    while (str1[i] != '\0')
    {
        if (find_character(str2, str1[i]) == NULL)
            break;
        match++;
        i++;
    }
    return (match);
}

/**
 * get_segment_length - Computes the segment of str1 which consists of characters not in str2.
 * @str1: The string to be searched.
 * @str2: The string to be used.
 *
 * Returns: The index at which a character in str1 exists in str2.
 */
int get_segment_length(char *str1, char *str2)
{
    int length = 0, i;

    for (i = 0; str1[i] != '\0'; i++)
    {
        if (find_character(str2, str1[i]) != NULL)
            break;
        length++;
    }
    return (length);
}

/**
 * find_character - Locates a character in a string.
 * @str: The string to be searched.
 * @c: The character to be checked.
 *
 * Returns: A pointer to the first occurrence of c in str.
 */
char *find_character(char *str, char c)
{
    int i = 0;

    for (; str[i] != c && str[i] != '\0'; i++)
        ;
    if (str[i] == c)
        return (str + i);
    else
        return (NULL);
}
