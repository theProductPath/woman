/*
 * get_topics.c -- get list of available topics from the manual file
 * Originally by Steven R. Jones, 1989
 *
 * Reads the manual data file. A line starting with an uppercase letter
 * is considered a topic heading.
 */

#include "woman.h"

int get_topics(char topic[][MAX_LEN])
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

    i = 0;
    while (fgets(string, MAX_LEN, fp) != NULL)
    {
        /* strip trailing newline */
        string[strcspn(string, "\n")] = '\0';

        if (isupper((unsigned char)string[0]) && i < MAX_ITEMS)
            strcpy(topic[i++], string);
    }

    fclose(fp);
    return i;
}
