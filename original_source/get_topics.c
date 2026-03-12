/*
 * get_topics -- routine to get list of available topics in manual
 */

#include "woman.h"

int get_topics(topic)
char    topic[][80];
{
    int         i;
    char        string[80];
    FILE        *fp;

    /* open file for reading */
    fp = fopen(WOMAN_FILE, "r");
    i = 0;

    while(fgets(string, 80, fp) != NULL)
        if (isupper(string[0]))
            strcpy(topic[i++], string);     /*if capital, then main topic */

    fclose(fp);
    return(i - 1);                          /* return number of topics found */
}
