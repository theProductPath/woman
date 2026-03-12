/*
 * pr_array.c -- print a screenful of items (topics or commands)
 * Originally by Steven R. Jones, 1989
 *
 * Formats command lines with aligned columns:
 *   command name padded to DESC_COL, then description
 * Topic lines (no tab) are printed with a small indent.
 */

#include "woman.h"

void print_array(char array[][MAX_LEN], int max)
{
    int     index = 0;
    int     row = BEGIN_ROW;
    char    formatted[MAX_LEN];
    char    *tab;

    while (index < max && index <= MAX_DISPLAY)
    {
        tab = strchr(array[index], '\t');
        if (tab != NULL)
        {
            /* command line: "cmd\tdescription" -> "    cmd         description" */
            int cmd_len = (int)(tab - array[index]);
            int pad = DESC_COL - CMD_COL - cmd_len;
            if (pad < 2) pad = 2;

            snprintf(formatted, sizeof(formatted), "%*s%-.*s%*s%s",
                     CMD_COL, "",               /* left indent */
                     cmd_len, array[index],     /* command name */
                     pad, "",                   /* padding to align descriptions */
                     tab + 1);                  /* description */

            mvaddstr(row++, 0, formatted);
        }
        else
        {
            /* topic line or plain text - small indent */
            snprintf(formatted, sizeof(formatted), "  %s", array[index]);
            mvaddstr(row++, 0, formatted);
        }
        index++;
    }

    refresh();
}
