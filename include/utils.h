#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define print(str, formats...)                                                \
  if (1)                                                                      \
    {                                                                         \
      char amogus[300] = "";                                                  \
      sprintf (amogus, str, formats);                                         \
      write (1, amogus, strlen (amogus));                                     \
    }
