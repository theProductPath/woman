/*
 * pr_heading.c -- print screen headings for the various pages
 * Originally by Steven R. Jones, 1989
 */

#include "woman.h"

void pr_heading(int choice, const char *xtra_str)
{
    switch (choice)
    {
        case 0:
        {
            /* introduction / title screen */
            clear();
            attron(A_REVERSE);
            mvaddstr(0, 0, " v. " VERSION " ");
            mvaddstr(0, 20, " Welcome to the WoMAN Pages ");
            mvaddstr(0, 60, " Steve Jones ");
            mvaddstr(1, 10, " Scroll through list and select a topic ");
            attroff(A_REVERSE);
            refresh();
            break;
        }

        case 1:
        {
            /* heading for command list page */
            clear();
            attron(A_REVERSE);
            mvaddstr(0, 3,
                " Scroll through the list of commands and choose one to look up ");
            mvprintw(1, 3, " Your topic -->  %s ", xtra_str);
            attroff(A_REVERSE);
            refresh();
            break;
        }

        case 2:
        {
            /* "hit return to continue" prompt */
            attron(A_REVERSE);
            mvaddstr(23, 22, " Hit RETURN to Continue ");
            attroff(A_REVERSE);
            refresh();
            getch();    /* wait for any key */
            break;
        }

        case 3:
        {
            /* heading while man page is loading */
            clear();
            attron(A_REVERSE);
            mvprintw(0, 0, " Getting man page for: %s ", xtra_str);
            attroff(A_REVERSE);
            refresh();
            break;
        }
    }
}
