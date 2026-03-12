/*
 * main.c - WOMAN main program
 * Steven R. Jones
 * Dec 8, 1989
 */

#include "woman.h"

main()
{
    int     flag;               /* when to jump out inner loop  */
    int     quit;               /* flag for outer loop          */
    int     done;               /* signal for man screen        */
    int     numtopics;          /* gets # of rids on main screen */
    int     numcommands;        /* number of commands            */
    int     index;              /* index thru list of topics    */
    int     currow;             /* current row on screen         */
    int     command;            /* command user chose from topic  */
    int     commandrow;         /* actual string pos for topic   */
    char    topic[80][80];      /* list of topics 80 for now    */
    char    command_str[80];    /* topic user chose              */
    char    topic_str[80];      /* 1st command on select         */
    char    *search_str;

    /* set up for curses */
    initscr();
    crmode();
    noecho();
    nonl();

    /* set defaults for CNTRL-C as tidy-up function */
    signal(SIGINT, end_prog);

    /* initialize to begin...start at beginning rows for both screens */
    currow = index = BEGIN_ROW;
    save = flag = 0;

    flag = TRUE;

    /* print heading on main page */
    pr_heading(0, "");

    /* get topics from file; store how many there are */
    numtopics = get_topics(topic);

    /* print array of topics and highlight first one */
    print_array(topic, numtopics);
    highlt(topic, &index, &currow);

    /* have user set topic to find command list for */
    strcpy(command_str, pick_topic(topic, &index, &currow, numtopics));

    /* if user chose quit clear and quit --- else continue */
    if (!strcmp(command_str, "Quit"))
        ;
    else
    {
        /* get commands for chosen topic; again store how many we got */
        /* always start on first row when coming to second screen 1st time */
        commandrow = BEGIN_ROW;
        numcommands = get_comm(command, topic_str);

        do
        {
            /* print command page heading -- it clears and refreshes */
            pr_heading(1, topic_str);

            /* function call to print commands --- and highlt first one */
            print_array(command, numcommands);
            highlt(command, &commandrow, &numcommands);

            /* call routine to get man page on */
            strcpy(topic_str, pick_topic(command, &commandrow, &numcommands,
                                         numcommands));

            if (!strcmp(command_str, "Quit"))
            {
                /* set flags to fall out of both loops */
                flag = FALSE;
                done = TRUE;
            }
            if (!strcmp(command_str, "Return"))
            {
                /* set flag to fall out of inner loop */
                flag = FALSE;
            }

            /* get command from entire line */
            strcpy(man_str, get_string(command_str));

            /* fork off process and have parent wait */
            if (flag && done)
            {
                pr_heading(3, man_str);
                signal(SIGINT, SIG_IGN);
                if (fork() == 0)
                {
                    /* child process */
                    execlp("man", "man", man_str, 0);
                }
                else
                {
                    /* in full-user function as being called */
                    pr_heading(3, "man", man_str, 0);
                    endwin();
                    wait(0);

                    /* re-enter in full-user to set return to continue */
                    pr_heading(2, "");
                }
            }
        } while (flag);
    }

    /* write */
    /* clean up -- set modes back to normal and quit */
    end_prog();

    /* comments about the program
     * control the scrolling of commands that take more than one page
     * topic CNTRL-d Group anywhere
     * blue CNTRL and directions
     */
}
