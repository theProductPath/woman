/*
 * woman.h - WOMAN header file
 *
 * Originally written by Steven R. Jones, Dec 8, 1989
 * Modernized for ncurses/POSIX systems, 2026
 *
 * WOMAN: a curses-based Unix command browser that organizes
 * commands by topic and provides a friendly interface to man pages.
 */

#ifndef WOMAN_H
#define WOMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ncurses.h>

#define VERSION     "2.0"
#define BEGIN_ROW   3
#define END_ROW     21
#define MAX_ITEMS   80
#define MAX_LEN     120
#define CMD_COL     4       /* left indent for command entries */
#define DESC_COL    20      /* column where descriptions start */
#define MAX_DISPLAY 19  /* max items visible on screen at once (0-indexed) */

/*
 * Default location for the manual data file.
 * Can be overridden at compile time with -DWOMAN_FILE="path"
 */
#ifndef WOMAN_FILE
#define WOMAN_FILE  "./manual"
#endif

/* Function prototypes */
void    end_prog(void);
void    pr_heading(int choice, const char *xtra_str);
void    print_array(char array[][MAX_LEN], int max);
char   *pick_topic(char topic[][MAX_LEN], int *index, int *currow, int numtopics);
void    highlt(char array[][MAX_LEN], int num, int currow);
void    dehighlt(char array[][MAX_LEN], int num, int currow);
int     get_topics(char topic[][MAX_LEN]);
int     get_comm(char command[][MAX_LEN], const char *search_str);
char   *get_string(const char *string);
void    show_story(void);

#endif /* WOMAN_H */
