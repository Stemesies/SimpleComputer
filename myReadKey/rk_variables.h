#ifndef RK_VARIABLES
#define RK_VARIABLES

#include <termios.h>
#include <unistd.h>

struct termios *getSavedRegime ();
struct termios *getCurrentRegime ();

#endif