#include "bc_variables.h"
#include <fcntl.h>
#include <include/myBigChars.h>
#include <stdlib.h>
#include <unistd.h>
int
bc_load (char *filename)
{
  int fd = open (filename, O_RDONLY);

  if (fd == -1)
    return -3;

  int count = 0;
  read (fd, &count, sizeof (int));

  bc_freeSpace ();
  unsigned char *buffer = (unsigned char *)malloc (count * BIGCHAR_HEIGHT
                                                   * sizeof (unsigned char));
  int actualSize = 0;

  if (buffer == NULL)
    return -4;

  int result = bc_bigcharread (fd, buffer, count, &actualSize);

  close (fd);

  bc_mallocSpace (actualSize);
  unsigned char *bfi = buffer;
  unsigned char *chars = getBigChars ();
  for (int i = 0; i < actualSize * BIGCHAR_HEIGHT; i++)
    {
      chars[i] = *bfi;
      bfi++;
    }

  return 0;
}