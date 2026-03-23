#include "include/mySimpleComputer.h"
#include "mySimpleComputer/sc_variables.h"
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void
IG (int signo)
{
  static struct itimerval nval;
  nval.it_interval.tv_usec = simulatonDelayUsecs;
  nval.it_interval.tv_sec = simulatonDelaySecs;
  nval.it_value.tv_usec = simulatonDelayUsecs;
  nval.it_value.tv_sec = simulatonDelaySecs;
  setitimer (ITIMER_REAL, &nval, NULL);

  ICR (signo);
}

void
IG_init ()
{
  signal (SIGALRM, IG);
  signal (SIGUSR1, IG);
  IG (SIGALRM);
}
