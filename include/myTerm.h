#ifndef MY_TERM
#define MY_TERM

typedef enum colors
{
  NOTHING = -1,
  RESET = 0,
  INVERSE = 7,
  BLACK = 30,
  RED = 31,
  GREEN = 32,
  YELLOW = 33,
  BLUE = 34,
  MAGENTA = 35,
  CYAN = 36,
  WHITE = 37,
  DEFAULT = 39,

  BRIGHT_BLACK = 90,
  BRIGHT_RED = 91,
  BRIGHT_GREEN = 92,
  BRIGHT_YELLOW = 93,
  BRIGHT_BLUE = 94,
  BRIGHT_MAGENTA = 95,
  BRIGHT_CYAN = 96,
  BRIGHT_WHITE = 97
} Colors;

int mt_alt ();
int mt_dealt ();

int mt_clrscr ();
int mt_delline ();

int mt_getscreensize (int *rows, int *columns);
int mt_gotoXY (int x, int y);

int mt_setbgcolor (enum colors);
int mt_setfgcolor (Colors);
int mt_setdefaultcolor ();

int mt_setcursorvisible (int value);

#endif