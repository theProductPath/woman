/*
 * get_comm.c -- get commands for a selected topic
 * Originally by Steven R. Jones, 1989
 *
 * Opens the manual file and finds the topic matching search_str.
 * Reads command entries beneath that topic until a blank line is hit.
 */

#include "woman.h"

int get_comm(char command[][MAX_LEN], const char *search_str)
{
    int     i;
    char    string[MAX_LEN];
    FILE    *fp;

    fp = fopen(WOMAN_FILE, "r");
    if (fp == NULL)
    {
        endwin();
        fprintf(stderr, "Error: cannot open manual file '%s'\n", WOMAN_FILE);
        exit(1);
    }

    /* find the matching topic line */
    while (fgets(string, MAX_LEN, fp) != NULL)
    {
        string[strcspn(string, "\n")] = '\0';
        if (strcmp(string, search_str) == 0)
            break;
    }

    /* read commands until blank line or EOF */
    i = 0;
    while (fgets(string, MAX_LEN, fp) != NULL && i < MAX_ITEMS)
    {
        /* a blank line (just newline) marks end of commands for this topic */
        if (string[0] == '\n' || string[0] == '\0')
            break;

        string[strcspn(string, "\n")] = '\0';
        strcpy(command[i], string);
        i++;
    }

    fclose(fp);

    /* pad rest of array */
    for (int y = i; y < MAX_ITEMS; y++)
        command[y][0] = '\0';

    return i;
}
