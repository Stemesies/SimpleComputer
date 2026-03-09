#ifndef BC_VARIABLES
#define BC_VARIABLES

#define BIGCHAR_WIDTH 8
#define BIGCHAR_HEIGHT 8

int getBigCharsLength ();

unsigned char *getBigChars ();

unsigned char *getBigChar (unsigned int id);

unsigned char *getNullChar ();

void setBigChars (unsigned char *bchars);

void setBigChar (unsigned int id, unsigned char *bchar);

#endif