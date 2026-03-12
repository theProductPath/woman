/*
 * get_comm.c -- get commands for selected topic
 */

#include "woman.h"

int get_comm(command, search_str)
char    command[30][80];
char    *search_str;
{
    int         i, y;
    char        string[80];
    FILE        *fp;

    /* open file for reading */
    if ((fp = fopen(WOMAN_FILE, "r")) == NULL)
    {
        printw("Error in open woman file.\n");
        refresh();
        exit(1);
    }

    i = 0;

    /* read till find matching topic */
    while(fgets(string, 80, fp) != NULL)
        if (!strcmp(string, search_str))
            break;

    /* read till I get a blank ; blank symbolizes end of commands for topic */
    while(fgets(command[i], 80, fp) != NULL)
    {
        if (!strcmp(command[i], "\n"))
            break;
        i++;
    }

    fclose(fp);

    /* pad rest of array with nulls */
    for (y = i; y < 20; y++)
        strcpy(command[y], "\0");

    /* return number of commands retrieved */
    return(i - 1);
}
