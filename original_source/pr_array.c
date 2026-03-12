/*
 * print_array() -- print a screenful(20 lines) of commands
 */

#include "woman.h"

print_array(array, max)
char    array[][80];
int     max;
{
    int     index = 0;
    int     row = BEGIN_ROW;

    while ( index <= max && index < 20 )
        mvaddstr(row++, 0, array[index++]);

    refresh();
}
