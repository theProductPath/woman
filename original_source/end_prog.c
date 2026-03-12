/*
 * end_prog.c
 * Function is last one called before termination of woman
 * designed to clean up the window and curses stuff;
 * Turns on echo to screen and turns off cbreak mode
 */

#include "woman.h"

int end_prog()
{
    echo();
    nocrmode();
    endwin();
}
