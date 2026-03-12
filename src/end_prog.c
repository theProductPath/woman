/*
 * end_prog.c
 * Originally by Steven R. Jones, 1989
 *
 * Cleans up the curses window and restores the terminal.
 */

#include "woman.h"

void end_prog(void)
{
    echo();
    nocbreak();
    endwin();
    exit(0);
}
