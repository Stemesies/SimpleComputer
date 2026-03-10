#include "bc_variables.h"
#include <fcntl.h>
#include <include/myBigChars.h>
#include <sys/stat.h>
#include <unistd.h>

int
bc_save (char *filename)
{
  int fd = open (filename, O_WRONLY | O_CREAT);

  if (fd == -1)
    return -3;

  int ahhh[] = { getBigCharsLength () };
  write (fd, ahhh, sizeof (int));
  int result = bc_bigcharwrite (fd, getBigChars (), getBigCharsLength ());
  close (fd);
  chmod (filename, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);

  return result;
}