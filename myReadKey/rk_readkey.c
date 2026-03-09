#include <include/myReadKey.h>
#include <sys/select.h>
#include <unistd.h>

static fd_set rfds;
static struct timeval tv;
long retval;

int
rk_readkey (Keys *keys)
{
  rk_mytermsave ();
  rk_mytermregime (0, 2, 0, 0, 1);

  retval = 0;
  while (read (0, &retval, 5) == 0)
    {
    }

  rk_mytermrestore ();
  *keys = (Keys)retval;
  return 0;
}
