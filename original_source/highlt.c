/*
 * highlt.c
 * Job: highlt.c
 * Date: Sun Apr 2 14:11:55 1989
 */

#include "woman.h"

/* highlt -- highlts the num index in the array */
highlt (array, num, currow)
char    array[][80];
int     num;
int     currow;
{
    standout();
    mvaddstr(currow, 0, array[num]);
    standend();
    refresh();
}

/* dehighlt -- highlts the num index in the array */
dehighlt(array, num, currow)
char    array[][80];
int     num;
int     currow;
{
    mvaddstr(currow, 0, array[num]);
    refresh();
}
