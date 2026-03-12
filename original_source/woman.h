/*
 * woman.h - WOMAN's own header file
 * Included in every function and procedure file.
 * Includes the other system libraries and defines
 * the more flexible, pre-processor variables.
 *
 * WOMAN v1.1
 * Steven R. Jones
 * Dec 8, 1989
 */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <ctype.h>
#include <signal.h>

#define BEGIN_ROW 3
#define END_ROW 21
#define WOMAN_FILE "./manual"
