/*
 * get_string.c -- extract the command name from a command line entry
 * Originally by Steven R. Jones, 1989
 *
 * Picks out the first word (the actual command name) from a line
 * that may contain a description after a tab or spaces.
 */

#include "woman.h"

char *get_string(const char *string)
{
    static char ret_str[MAX_LEN];
    int index = 0;

    /* copy characters until we hit a tab, space, or end of string */
    while (string[index] != '\0' &&
           string[index] != '\t' &&
           string[index] != ' ')
    {
        ret_str[index] = string[index];
        index++;
        if (index >= MAX_LEN - 1)
            break;
    }

    ret_str[index] = '\0';
    return ret_str;
}
