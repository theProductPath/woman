/*
 * pick_topic -- lets user cruise through list of topics/commands
 *   if user changes index,currow, keep track and return modified values
 */

#include "woman.h"

char *pick_topic(topic, index, currow, numtopics)
char    topic[][80];
int     *index, *currow, numtopics;
{
    char    input;              /* to get user input */
    char    return_str[80];    /* to return user selection */

    /* print appropriate opening message */
    standout();
    if (isupper(topic[0][0]))
        mvaddstr(23, 1,
            "H - HELP  J - DOWN  K - UP  T - TOP  B - BOTTOM  <CR> accepts  Q - QUIT!");
    else
        mvaddstr(23, 4,
            "H - HELP  R - RET  J - DOWN  K - UP  T - TOP  B - BOT  <CR> accepts");
    standend();
    move(23, 72);           /* move cursor to end of bottom line */
    refresh();

    /* big loop to get and respond to user input */
    while (input = getch())
    {
        switch (toupper(input))
        {
            case 'J':           /* j is down; if at bottom, go back to top */
            {
                if ((*index) == numtopics || (*index) == 19)
                {
                    dehighlt(topic, *index, *currow);
                    *index = 0;
                    *currow = BEGIN_ROW;
                    highlt(topic, *index, *currow);
                }
                else
                {
                    dehighlt(topic, *index, *currow);
                    (*index) ++;
                    (*currow) ++;
                    highlt(topic, *index, *currow);
                }
                break;
            }

            case 'K':           /* k is up ; if at top, goto bottom */
            {
                if ( *index == 0 )
                {
                    dehighlt(topic, *index, *currow);
                    if (numtopics < 19)
                    {
                        *index = numtopics;
                        *currow = BEGIN_ROW + numtopics;
                    }
                    else
                    {
                        *index = 19;
                        *currow = BEGIN_ROW + 19;
                    }

                    highlt(topic, *index, *currow);
                }
                else
                {
                    dehighlt(topic, *index, *currow);
                    (*index)--;
                    (*currow)--;
                    highlt(topic, *index, *currow);
                }
                break;
            }

            case 'T':           /* t takes user to top of list */
            {
                dehighlt(topic, *index, *currow);
                *currow = BEGIN_ROW;
                *index = 0;
                highlt(topic, *index, *currow);
                break;
            }

            case 'B':           /* b takes user to bottom of list */
            {
                dehighlt(topic, *index, *currow);
                *currow = BEGIN_ROW + numtopics;
                if (numtopics < 19)
                {
                    *index = numtopics;
                    *currow = BEGIN_ROW + numtopics;
                }
                else
                {
                    *index = 19;
                    *currow = BEGIN_ROW + 19;
                }
                highlt(topic, *index, *currow);
                break;
            }

            case 'H':           /* h calls help page */
            {
                clear();
                refresh();
                system("cat woman_help");
                pr_heading(2, "");

                /* after coming back from help, check to see what page and re-
                   print correct heading and associated array */
                if (isupper(topic[0][0]))
                {
                    pr_heading(0, "");    standout();
                    mvaddstr(23, 1, "H - HELP  J - DOWN  K - UP  T - TOP  B - BOTTOM");
                    standend();   refresh();
                }
                else
                {
                    pr_heading(1, "");    standout();
                    mvaddstr(23, 4, "H - HELP  R - RET  J - DOWN  K - UP  T - TOP  ");
                    standend();   refresh();
                }

                /* print array of topics again and highlight first one */
                print_array(topic, numtopics);
                highlt(topic, *index, *currow);

                break;
            }

            case '\n':          /* newline signifies user chose current index */
            {
                input = 'Q';   /* break out of input loop */
                strcpy(return_str, topic[*index]);
                break;
            }

            case 'R':           /* on second page if user types Return       */
            {                   /* we send him/her back to first page         */
                if (isupper(topic[0][0]))
                                /* if on first page, do nothing              */
                    ;
                else
                {
                    clear();
                    refresh();
                    input = 'Q';
                    strcpy(return_str, "Return");
                }
                break;
            }

            case 'Q':           /* q is for quit, jump out of loop */
            {
                clear();
                refresh();
                strcpy(return_str, "Quit");
                break;
            }

            default:
                break;
        }

        if (toupper(input) == 'Q')
            break;
        else
        {
                            /* move cursor back to end of bottom line */
            move(23, 72);
            refresh();
        }
    }

    return(return_str); /* return either "Return", "Quit", or chosen topic */
}
