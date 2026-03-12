/*
 * pick_topic.c -- interactive topic/command browser
 * Originally by Steven R. Jones, 1989
 *
 * Lets the user navigate through a list with vi-style keys (j/k)
 * and select an item with Enter. Returns the selected string,
 * "Return" to go back, or "Quit" to exit.
 */

#include "woman.h"

char *pick_topic(char topic[][MAX_LEN], int *index, int *currow, int numtopics)
{
    int     input;
    static char return_str[MAX_LEN];
    int     is_topic_page;
    int     max_visible;

    is_topic_page = isupper((unsigned char)topic[0][0]);
    max_visible = (numtopics <= MAX_DISPLAY) ? numtopics - 1 : MAX_DISPLAY;

    /* print navigation help at the bottom */
    attron(A_REVERSE);
    if (is_topic_page)
        mvaddstr(23, 1,
            " J-Down K-Up T-Top B-Bot Enter-Select H-Help S-Story Q-Quit ");
    else
        mvaddstr(23, 1,
            " J-Down K-Up T-Top B-Bot Enter-Select R-Return H-Help Q-Quit ");
    attroff(A_REVERSE);
    move(23, 75);
    refresh();

    /* main input loop */
    while ((input = getch()) != ERR)
    {
        switch (toupper(input))
        {
            case 'J':       /* down - wrap to top at bottom */
            case KEY_DOWN:
            {
                dehighlt(topic, *index, *currow);
                if (*index >= max_visible)
                {
                    *index = 0;
                    *currow = BEGIN_ROW;
                }
                else
                {
                    (*index)++;
                    (*currow)++;
                }
                highlt(topic, *index, *currow);
                break;
            }

            case 'K':       /* up - wrap to bottom at top */
            case KEY_UP:
            {
                dehighlt(topic, *index, *currow);
                if (*index <= 0)
                {
                    *index = max_visible;
                    *currow = BEGIN_ROW + max_visible;
                }
                else
                {
                    (*index)--;
                    (*currow)--;
                }
                highlt(topic, *index, *currow);
                break;
            }

            case 'T':       /* jump to top */
            {
                dehighlt(topic, *index, *currow);
                *currow = BEGIN_ROW;
                *index = 0;
                highlt(topic, *index, *currow);
                break;
            }

            case 'B':       /* jump to bottom */
            {
                dehighlt(topic, *index, *currow);
                *index = max_visible;
                *currow = BEGIN_ROW + max_visible;
                highlt(topic, *index, *currow);
                break;
            }

            case 'H':       /* help screen */
            {
                clear();
                mvaddstr(2, 10, "=== WoMAN Help ===");
                mvaddstr(4, 5, "Navigation:");
                mvaddstr(5, 8, "J or Down Arrow  - Move down");
                mvaddstr(6, 8, "K or Up Arrow    - Move up");
                mvaddstr(7, 8, "T                - Jump to top of list");
                mvaddstr(8, 8, "B                - Jump to bottom of list");
                mvaddstr(10, 5, "Actions:");
                mvaddstr(11, 8, "Enter            - Select highlighted item");
                mvaddstr(12, 8, "R                - Return to previous page");
                mvaddstr(13, 8, "H                - Show this help screen");
                mvaddstr(14, 8, "S                - The story behind WoMAN");
                mvaddstr(15, 8, "Q                - Quit WoMAN");
                mvaddstr(17, 5, "WoMAN displays Unix commands organized by topic.");
                mvaddstr(18, 5, "Select a topic to see its commands, then select");
                mvaddstr(19, 5, "a command to view its man page.");

                attron(A_REVERSE);
                mvaddstr(23, 22, " Hit any key to continue ");
                attroff(A_REVERSE);
                refresh();
                getch();

                /* redraw the page we came from */
                if (is_topic_page)
                    pr_heading(0, "");
                else
                    pr_heading(1, "");

                print_array(topic, numtopics);
                highlt(topic, *index, *currow);

                /* redraw nav bar */
                attron(A_REVERSE);
                if (is_topic_page)
                    mvaddstr(23, 1,
                        " J-Down K-Up T-Top B-Bot Enter-Select H-Help S-Story Q-Quit ");
                else
                    mvaddstr(23, 1,
                        " J-Down K-Up T-Top B-Bot Enter-Select R-Return H-Help Q-Quit ");
                attroff(A_REVERSE);
                refresh();
                break;
            }

            case '\n':      /* Enter - select current item */
            case '\r':
            case KEY_ENTER:
            {
                strcpy(return_str, topic[*index]);
                return return_str;
            }

            case 'R':       /* return to previous page (command page only) */
            {
                if (!is_topic_page)
                {
                    clear();
                    refresh();
                    strcpy(return_str, "Return");
                    return return_str;
                }
                break;
            }

            case 'S':       /* story - only on topic page */
            {
                if (is_topic_page)
                {
                    show_story();

                    /* redraw the topic page */
                    pr_heading(0, "");
                    print_array(topic, numtopics);
                    highlt(topic, *index, *currow);

                    /* redraw nav bar */
                    attron(A_REVERSE);
                    mvaddstr(23, 1,
                        " J-Down K-Up T-Top B-Bot Enter-Select H-Help S-Story Q-Quit ");
                    attroff(A_REVERSE);
                    refresh();
                }
                break;
            }

            case 'Q':       /* quit */
            {
                clear();
                refresh();
                strcpy(return_str, "Quit");
                return return_str;
            }

            default:
                break;
        }

        move(23, 75);
        refresh();
    }

    strcpy(return_str, "Quit");
    return return_str;
}
