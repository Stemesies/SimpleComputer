
#ifndef MY_BIG_CHARS_HEADER
#define MY_BIG_CHARS_HEADER

#include <include/myTerm.h>

int bc_strlen (char *str);
int bc_printA (char *str);

int bc_box (int x1, int y1, int x2, int y2, Colors box_fg, Colors box_bg,
            char *header, Colors header_fg, Colors header_bg);

int bc_getbigcharpos (unsigned char *big, int x, int y, int *value);
int bc_setbigcharpos (unsigned char *big, int x, int y, int value);
int bc_printbigchar (int big, int x, int y, Colors fg, Colors bg);

void bc_setBigChar (unsigned int id, unsigned char *bchar);
void bc_freeSpace ();
unsigned char *bc_mallocSpace (int count);

int bc_chartoglyph (char chara);

int bc_bigcharwrite (int fd, unsigned char *big, int count);
int bc_bigcharread (int fd, unsigned char *big, int need_count, int *count);

int bc_save (char *filename);
int bc_load (char *filename);
int bc_trim (int count);

#endif