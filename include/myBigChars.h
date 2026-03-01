
#ifndef MY_BIG_CHARS_HEADER
#define MY_BIG_CHARS_HEADER

#include <include/myTerm.h>

int bc_strlen (char *str);
int bc_printA (char *str);

int bc_box (int x1, int y1, int x2, int y2, Colors box_fg, Colors box_bg,
            char *header, Colors header_fg, Colors header_bg);

#endif