/*
 * get_string -- picks out search string from command line
 */

#include "woman.h"

char    *get_string(string)
char    *string;
{
    char        ret_str[25];
    char        c;
    int         index;

    index = 0;
    /* copy char by char till reach tab or blank */
    while ((c = string[index]) != '\t' && c != ' ')
    {
        ret_str[index] = string[index];
        index++;
    }

    /* terminate with null */
    ret_str[index] = '\0';

    /* return copied, shorter string */
    return (ret_str);
}
