#include "bc_variables.h"
#include <stdlib.h>

unsigned char *bigchars = 0;
int bigcharsLength = -1;

unsigned char nullChar[8] = { 0U, 126U, 66U, 66U, 66U, 66U, 126U, 0U };

int
getBigCharsLength ()
{
  return bigcharsLength;
}

unsigned char *
getBigChars ()
{
  return bigchars;
}

unsigned char *
getBigChar (unsigned int id)
{
  return bigchars + (id * BIGCHAR_HEIGHT);
}

unsigned char *
getNullChar ()
{
  return nullChar;
}

void
setBigChars (unsigned char *bchars)
{
  bigchars = bchars;
}

void
bc_setBigChar (unsigned int id, unsigned char *bchar)
{
  for (int i = 0; i < 8; i++)
    bigchars[(id * 8) + i] = bchar[i];
}

void
bc_freeSpace ()
{
  free (bigchars);
  bigchars = 0;
  bigcharsLength = -1;
}

unsigned char *
bc_mallocSpace (int count)
{
  if (bigcharsLength != -1)
    return 0;

  bigchars = (unsigned char *)calloc (count * BIGCHAR_HEIGHT, sizeof (char));
  bigcharsLength = count;
  return bigchars;
}

int
bc_trim (int count)
{
  if (count <= -1)
    return -1;
  bigcharsLength = count;
  return 0;
}