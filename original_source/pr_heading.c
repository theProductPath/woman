/*
 * pr_heading -- will print a variety of headings depending on choice
 */

#include "woman.h"

int pr_heading(choice, xtra_str)
int     choice;
char    *xtra_str;
{
    switch (choice)
    {
        case 0: {
            /* introduction for first page */
            clear();
            standout();
            mvaddstr(0, 0, "v. 1.0");
            mvaddstr(0, 20, "Welcome to the WoMAN Pages");
            mvaddstr(0, 67, "Steve Jones");
            mvaddstr(1, 13, "Scroll through list and select a topic");
            standend();
            break;
        }

        case 1: {
            /* heading for second page */
            clear();
            standout();
            mvaddstr(0, 5,
                "Scroll through the list of commands and choose one to look up");
            mvaddstr(1, 5, "Your topic -->  ");
            mvaddstr(1, 19, xtra_str);      /* here xtra_str is topic user chose*/
            standend();
            refresh();
            break;
        }

        case 2: {
            /* universal message for bottom of page prompt and input */
            standout();
            mvaddstr(23, 22, "Hit RETURN to Continue");
            standend();
            refresh();
            while ( mvgetch(23, 44) != '\n' )
                ;
            break;
        }

        case 3: {
            /* heading while waiting for man page to process */
            clear();
            standout();
            mvaddstr(0, 0, "Getting man page for ");
            mvaddstr(0, 21, xtra_str);
            standend();
            refresh();
            break;
        }
    }
}
