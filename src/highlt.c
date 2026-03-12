/*
 * highlt.c -- highlight and dehighlight items in the curses display
 * Originally by Steven R. Jones, Apr 2, 1989
 *
 * Uses curses reverse video to visually indicate the selected item.
 * Formats command lines with aligned columns to match print_array.
 */

#include "woman.h"

/* format a line for display, aligning command/description columns */
static void format_line(const char *raw, char *out, int outsize)
{
    const char *tab = strchr(raw, '\t');
    if (tab != NULL)
    {
        int cmd_len = (int)(tab - raw);
        int pad = DESC_COL - CMD_COL - cmd_len;
        if (pad < 2) pad = 2;

        snprintf(out, outsize, "%*s%-.*s%*s%s",
                 CMD_COL, "",
                 cmd_len, raw,
                 pad, "",
                 tab + 1);
    }
    else
    {
        snprintf(out, outsize, "  %s", raw);
    }
}

void highlt(char array[][MAX_LEN], int num, int currow)
{
    char formatted[MAX_LEN];
    int  width = COLS;  /* terminal width from ncurses */

    format_line(array[num], formatted, sizeof(formatted));

    /* pad to full terminal width so the entire row highlights */
    int len = (int)strlen(formatted);
    while (len < width - 1 && len < MAX_LEN - 1)
        formatted[len++] = ' ';
    formatted[len] = '\0';

    attron(A_REVERSE);
    mvaddstr(currow, 0, formatted);
    attroff(A_REVERSE);
    refresh();
}

void dehighlt(char array[][MAX_LEN], int num, int currow)
{
    char formatted[MAX_LEN];

    format_line(array[num], formatted, sizeof(formatted));

    /* clear the full row first to remove any leftover highlight padding */
    move(currow, 0);
    clrtoeol();
    mvaddstr(currow, 0, formatted);
    refresh();
}
