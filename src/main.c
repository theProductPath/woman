/*
 * WOMAN - WoMAN Pages
 * A curses-based Unix command browser
 *
 * Originally written by Steven R. Jones
 * December 8, 1989
 *
 * Rebuilt and modernized, March 2026
 *
 * WOMAN was created because Unix man pages were great once you knew
 * a command existed, but offered no way to discover commands in the
 * first place. This program organizes available Unix commands by topic,
 * lets you browse them with short descriptions, and then opens the
 * man page for any command you choose.
 */

#include "woman.h"

static void show_404(const char *cmd_name)
{
    clear();

    attron(A_REVERSE);
    mvaddstr(0, 0,
        "                                                "
        "                                ");
    mvaddstr(0, 25, " WoMAN  -  Page Not Found ");
    attroff(A_REVERSE);

    mvaddstr(3,  10, "    _  _    ___  _  _");
    mvaddstr(4,  10, "   | || |  / _ \\| || |");
    mvaddstr(5,  10, "   | || |_| | | | || |_");
    mvaddstr(6,  10, "   |__  _| | | |__  _|");
    mvaddstr(7,  10, "      | | | |_| |  | |");
    mvaddstr(8,  10, "      |_|  \\___/   |_|");

    mvaddstr(11, 10, "No manual entry found for:");
    attron(A_BOLD);
    mvaddstr(11, 37, cmd_name);
    attroff(A_BOLD);

    mvaddstr(13, 10, "This command may not be installed on your");
    mvaddstr(14, 10, "system, or its man page may be missing.");
    mvaddstr(16, 10, "Try installing it with your package manager,");
    mvaddstr(17, 10, "or search online for documentation.");

    mvaddstr(19, 10, "In 1989, this would have meant a trip to");
    mvaddstr(20, 10, "the campus computer lab to ask someone.");

    attron(A_REVERSE);
    mvaddstr(23, 22, " Hit any key to continue ");
    attroff(A_REVERSE);
    refresh();
    getch();
}

int main(int argc, char *argv[])
{
    int     numtopics;
    int     numcommands;
    int     topic_index;
    int     topic_currow;
    int     cmd_index;
    int     cmd_currow;
    int     running;
    char    topic[MAX_ITEMS][MAX_LEN];
    char    command[MAX_ITEMS][MAX_LEN];
    char    *selection;
    char    *cmd_name;
    char    topic_str[MAX_LEN];
    pid_t   pid;

    /* set up curses */
    initscr();
    cbreak();
    noecho();
    nonl();
    keypad(stdscr, TRUE);   /* enable arrow keys */

    /* handle CTRL-C gracefully */
    signal(SIGINT, (void (*)(int))end_prog);

    /* load topics from the manual file */
    numtopics = get_topics(topic);
    if (numtopics == 0)
    {
        endwin();
        fprintf(stderr, "No topics found in '%s'\n", WOMAN_FILE);
        return 1;
    }

    running = 1;

    while (running)
    {
        /* display the topic selection page */
        pr_heading(0, "");
        print_array(topic, numtopics);

        topic_index = 0;
        topic_currow = BEGIN_ROW;
        highlt(topic, topic_index, topic_currow);

        /* let user pick a topic */
        selection = pick_topic(topic, &topic_index, &topic_currow, numtopics);

        if (strcmp(selection, "Quit") == 0)
        {
            running = 0;
            break;
        }

        /* copy the selected topic name */
        strcpy(topic_str, selection);

        /* get commands for the selected topic */
        numcommands = get_comm(command, topic_str);
        if (numcommands == 0)
            continue;

        /* command browsing loop */
        while (1)
        {
            pr_heading(1, topic_str);
            print_array(command, numcommands);

            cmd_index = 0;
            cmd_currow = BEGIN_ROW;
            highlt(command, cmd_index, cmd_currow);

            selection = pick_topic(command, &cmd_index, &cmd_currow, numcommands);

            if (strcmp(selection, "Quit") == 0)
            {
                running = 0;
                break;
            }

            if (strcmp(selection, "Return") == 0)
                break;  /* back to topic list */

            /* extract the command name (first word before tab/space) */
            cmd_name = get_string(selection);

            /* show a brief "how to use man" overlay before launching */
            clear();
            attron(A_REVERSE);
            mvprintw(0, 0, "%*s", 80, "");  /* full-width bar */
            mvprintw(0, 15, " Opening man page for: %s ", cmd_name);
            attroff(A_REVERSE);

            mvaddstr(3,  10, "You are about to enter the manual page");
            mvaddstr(4,  10, "viewer.  Here's how to navigate:");
            mvaddstr(6,  14, "Space / f     Next page");
            mvaddstr(7,  14, "b             Previous page");
            mvaddstr(8,  14, "Up/Down       Scroll line by line");
            mvaddstr(9,  14, "/pattern      Search for text");
            mvaddstr(10, 14, "n             Next search result");
            mvaddstr(12, 14, "q             Quit and return to WoMAN");

            mvaddstr(15, 10, "The manual page will fill your terminal.");
            mvaddstr(16, 10, "When you're done reading, press 'q' to");
            mvaddstr(17, 10, "come back here.");

            attron(A_REVERSE);
            mvaddstr(23, 18, " Press any key to open the man page ");
            attroff(A_REVERSE);
            refresh();
            getch();

            /* show loading heading and launch man */
            pr_heading(3, cmd_name);

            /* temporarily leave curses mode to show man page */
            def_prog_mode();
            endwin();

            pid = fork();
            if (pid == 0)
            {
                /* child: exec man */
                execlp("man", "man", cmd_name, (char *)NULL);
                /* if exec fails */
                perror("man");
                _exit(1);
            }
            else if (pid > 0)
            {
                /* parent: wait for man to finish */
                int status;
                waitpid(pid, &status, 0);

                /* re-enter curses mode */
                reset_prog_mode();
                refresh();

                /* check if man page was found */
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
                    show_404(cmd_name);
                else
                    pr_heading(2, "");
            }
            else
            {
                /* fork failed - re-enter curses */
                reset_prog_mode();
                refresh();
                show_404(cmd_name);
            }
        }
    }

    end_prog();
    return 0;
}
