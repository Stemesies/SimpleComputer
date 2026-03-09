#include "rk_variables.h"

struct termios currentRegime = {};
struct termios savedRegime = {};

struct termios *
getSavedRegime ()
{
  return &savedRegime;
}

struct termios *
getCurrentRegime ()
{
  return &currentRegime;
}