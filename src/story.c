/*
 * story.c -- "The Story of WoMAN" - an embedded retrospective
 *
 * A multi-page narrative viewable from within the program,
 * rendered to look like continuous tractor-feed printer paper
 * with sprocket holes and perforation lines.
 *
 * Designed for a standard 80x24 terminal.
 *
 * Layout (80 columns):
 *   Cols 0-3:   left tractor strip  ("O | " or "  | ")
 *   Cols 4-75:  paper content area   (72 chars)
 *   Cols 76-79: right tractor strip  (" | O" or " |  ")
 *
 * Sprocket holes alternate every other row.
 * Perforation lines mark page boundaries top and bottom.
 */

#include "woman.h"

/* --- tractor-feed drawing primitives --- */

static void draw_perforation(int row)
{
    /* -O-+--- ... ---+-O- */
    char line[81];
    memset(line, '-', 80);
    line[80] = '\0';
    line[1] = 'O';
    line[3] = '+';
    line[76] = '+';
    line[78] = 'O';
    mvaddstr(row, 0, line);
}

static void draw_paper_line(int row, const char *text, int has_hole)
{
    char line[81];
    int textlen, i;

    memset(line, ' ', 80);
    line[80] = '\0';

    /* left tractor strip */
    if (has_hole)
    {
        line[0] = 'O';
        line[2] = '|';
    }
    else
    {
        line[2] = '|';
    }

    /* right tractor strip */
    if (has_hole)
    {
        line[76] = ' ';
        line[77] = '|';
        line[79] = 'O';
    }
    else
    {
        line[77] = '|';
    }

    /* place text content starting at column 5 (one space past the pipe) */
    if (text != NULL)
    {
        textlen = (int)strlen(text);
        if (textlen > 71) textlen = 71;   /* max content width */
        for (i = 0; i < textlen; i++)
            line[5 + i] = text[i];
    }

    mvaddstr(row, 0, line);
}

/* --- story page content --- */
/* Each text line must be <= 70 chars to fit inside the paper frame.  */
/* NULL terminates each page's content.                                */

static const char *page1[] = {
    "",
    "  T H E   S T O R Y   O F   W o M A N",
    "",
    "  A retrospective, 36 years later",
    "  Originally written December 8, 1989",
    "  by Steven R. Jones",
    "",
    "",
    "  +-------------------------------------------------+",
    "  |  \"WOMAN was developed on our UNIX systems       |",
    "  |   after a considerable number of complaints     |",
    "  |   had arisen with respect to the existing       |",
    "  |   man pages.\"                                   |",
    "  |              -- Technical Reference, v1.1       |",
    "  +-------------------------------------------------+",
    "",
    NULL
};

static const char *page2[] = {
    "",
    "  I. The Problem",
    "  ~~~~~~~~~~~~~~",
    "",
    "  In 1989, Unix was powerful but cryptic.",
    "",
    "  If you already knew a command existed, the",
    "  man pages were an excellent reference. Type",
    "  'man ls' and you'd get everything you needed.",
    "",
    "  But what if you didn't know 'ls' existed?",
    "",
    "  What if you were a new user, sitting in front",
    "  of a blinking cursor on a VT100 terminal, and",
    "  you wanted to copy a file or check who else",
    "  was logged in?  There was no menu. No search.",
    "  You either knew, or you asked someone who did.",
    NULL
};

static const char *page3[] = {
    "",
    "  II. The Solution",
    "  ~~~~~~~~~~~~~~~~",
    "",
    "  Steven R. Jones was a college student learning",
    "  Unix. He saw the gap: the man pages were a",
    "  reference manual with no table of contents.",
    "  A dictionary with no way to browse.",
    "",
    "  So he built one.",
    "",
    "  He called it WoMAN -- a play on the 'man'",
    "  command. Where 'man' required you to already",
    "  know what you needed, WoMAN showed you what",
    "  was available. Organized by topic. With short",
    "  descriptions so you could learn what each",
    "  command did before reading the full manual.",
    NULL
};

static const char *page4[] = {
    "",
    "  III. The Interface",
    "  ~~~~~~~~~~~~~~~~~~",
    "",
    "  In 1989, Unix was entirely text-driven. You",
    "  typed commands. You read output. That was it.",
    "  No graphical interfaces. No mice. No menus.",
    "",
    "  But there was curses.",
    "",
    "  The curses library let a programmer take over",
    "  the terminal -- position text anywhere, high-",
    "  light selections, respond to keystrokes live.",
    "  It was the same library that powered games",
    "  like NetHack and Rogue.",
    "",
    "  Using curses, Jones built something that felt",
    "  like a graphical application inside a text",
    NULL
};

static const char *page5[] = {
    "",
    "  terminal: a menu you could navigate with",
    "  keys, with highlighted selections and screens",
    "  organized like pages in a book.",
    "",
    "  It wasn't a GUI. But it was the closest thing",
    "  Unix users had seen for browsing documentation",
    "  -- a visual interface before visual interfaces",
    "  existed on these systems.",
    "",
    "  In modern terms, it was a UX decision. Don't",
    "  just document the system. Make it discoverable.",
    "  Make it browsable. Make it friendly.",
    "",
    "  This was product thinking -- years before he",
    "  would have a name for it.",
    "",
    NULL
};

static const char *page6[] = {
    "",
    "  IV. The Design",
    "  ~~~~~~~~~~~~~~",
    "",
    "  The program read from a simple data file",
    "  called 'manual'. Topics were identified by",
    "  an uppercase first letter. Commands listed",
    "  beneath each topic, tab-separated from their",
    "  descriptions. A blank line ended each section.",
    "",
    "  Anyone could customize WoMAN for their system",
    "  -- add commands, create categories, even re-",
    "  purpose it for different reference material.",
    "  The program didn't need to change. Just the",
    "  data file. A platform with configurable data.",
    "",
    "  The campus IT department adopted WoMAN and",
    "  deployed it across the university's systems.",
    NULL
};

static const char *page7[] = {
    "",
    "  V. The Resurrection",
    "  ~~~~~~~~~~~~~~~~~~~",
    "",
    "                     * * *",
    "",
    "  Thirty-six years later, in March 2026,",
    "  Steven Jones found two documents from 1989:",
    "  a printout of the source code and a technical",
    "  reference manual for WoMAN version 1.1,",
    "  dated December 8, 1989.",
    "",
    "  Dot-matrix printouts. Three-hole-punched",
    "  paper. Handwritten labels in the margins",
    "  identifying each source file. Tractor-feed",
    "  strips still attached on some pages.",
    "",
    "  No digital copies of the code had survived.",
    NULL
};

static const char *page8[] = {
    "",
    "  Using AI, the source code was visually read",
    "  from the scanned images -- character by char-",
    "  acter from 15 pages of faded printout.",
    "",
    "  The code was modernized from K&R C to compile",
    "  on current systems, and rebuilt with ncurses",
    "  -- the modern descendant of the same curses",
    "  library used in 1989.",
    "",
    "  The program you are running right now is that",
    "  rebuild. These lines are rendered by the same",
    "  curses functions, the same highlight routines,",
    "  the same screen layout -- just recompiled for",
    "  a world that didn't exist when they were first",
    "  written.",
    "",
    NULL
};

static const char *page9[] = {
    "",
    "  VI. The Return",
    "  ~~~~~~~~~~~~~~",
    "",
    "  There is something fitting about WoMAN",
    "  returning now.",
    "",
    "  In 2026, the command line is having a moment.",
    "  Developers work in terminals again -- using",
    "  AI-powered tools like Claude Code and Cursor",
    "  that bring intelligence to the same text-based",
    "  environment WoMAN was designed for in 1989.",
    "",
    "  The insight that drove WoMAN -- that powerful",
    "  systems need discoverable interfaces, that",
    "  users shouldn't have to already know what",
    "  they're looking for -- is exactly the insight",
    "  driving today's AI-powered terminals.",
    NULL
};

static const char *page10[] = {
    "",
    "  WoMAN was built before 'product management'",
    "  was a common title in software. But it was a",
    "  product from the start: a problem identified,",
    "  a solution designed, an experience crafted,",
    "  and users served.",
    "",
    "  Some things don't change in 36 years.",
    "  Some things just come back around.",
    "",
    "",
    "  +-------------------------------------------------+",
    "  |  WoMAN v1.1  -  December 8, 1989               |",
    "  |  WoMAN v2.0  -  March 2026                     |",
    "  |  Steven R. Jones                                |",
    "  +-------------------------------------------------+",
    "",
    NULL
};

#define NUM_STORY_PAGES 10

static const char **story_pages[NUM_STORY_PAGES] = {
    page1, page2, page3, page4, page5,
    page6, page7, page8, page9, page10
};

static const char *page_titles[NUM_STORY_PAGES] = {
    "Title Page",
    "The Problem",
    "The Solution",
    "The Interface",
    "The Interface (cont.)",
    "The Design",
    "The Resurrection",
    "The Resurrection (cont.)",
    "The Return",
    "The Return (cont.)"
};

/* --- main story display function --- */

void show_story(void)
{
    int current_page = 0;
    int input;
    int row, i;
    const char **lines;
    int line_idx;
    char header[81];
    char footer[81];

    while (1)
    {
        clear();

        /* row 0: header bar (reverse video, outside the "paper") */
        snprintf(header, sizeof(header),
                 " The Story of WoMAN  |  %d of %d: %s",
                 current_page + 1, NUM_STORY_PAGES,
                 page_titles[current_page]);
        attron(A_REVERSE);
        mvaddstr(0, 0, header);
        for (i = (int)strlen(header); i < 80; i++)
            addch(' ');
        attroff(A_REVERSE);

        /* row 1: top perforation */
        draw_perforation(1);

        /* rows 2-21: paper content with tractor feed strips */
        lines = story_pages[current_page];
        line_idx = 0;

        for (row = 2; row <= 21; row++)
        {
            int has_hole = (row % 2 == 0);  /* holes on even rows */
            const char *text = NULL;

            if (lines[line_idx] != NULL)
            {
                text = lines[line_idx];
                line_idx++;
            }

            draw_paper_line(row, text, has_hole);
        }

        /* row 22: bottom perforation */
        draw_perforation(22);

        /* row 23: navigation footer (reverse video, outside "paper") */
        attron(A_REVERSE);
        if (current_page == 0)
            snprintf(footer, sizeof(footer),
                "  Enter/Right - Next Page    Q - Back to WoMAN"
                "            Page 1 of %d  ", NUM_STORY_PAGES);
        else if (current_page == NUM_STORY_PAGES - 1)
            snprintf(footer, sizeof(footer),
                "  Left - Prev    Q - Back to WoMAN"
                "                  Page %d of %d  ",
                NUM_STORY_PAGES, NUM_STORY_PAGES);
        else
            snprintf(footer, sizeof(footer),
                "  Left/Right - Navigate    Q - Back to WoMAN"
                "          Page %d of %d  ",
                current_page + 1, NUM_STORY_PAGES);

        mvaddstr(23, 0, footer);
        for (i = (int)strlen(footer); i < 80; i++)
            addch(' ');
        attroff(A_REVERSE);

        refresh();

        /* handle input */
        input = getch();
        switch (input)
        {
            case 'q':
            case 'Q':
                return;

            case '\n':
            case '\r':
            case KEY_ENTER:
            case KEY_RIGHT:
            case 'l':
            case 'j':
            case ' ':
                if (current_page < NUM_STORY_PAGES - 1)
                    current_page++;
                else
                    return;
                break;

            case KEY_LEFT:
            case KEY_BACKSPACE:
            case 127:
            case 'h':
            case 'k':
                if (current_page > 0)
                    current_page--;
                break;

            default:
                break;
        }
    }
}
