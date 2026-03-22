#include <include/mySimpleComputer.h>
#include <signal.h>
#include <sys/time.h>

static struct itimerval nval = { .it_interval = { 0, TICK_DELAY * 1000 },
                                 .it_value = { 0, TICK_DELAY * 1000 } },
                        oval;

void
IG (int signo)
{
  ICR (signo);
  setitimer (ITIMER_REAL, &nval, &oval);
}

void
IG_init ()
{
  signal (SIGALRM, IG);
  signal (SIGUSR1, IG);
  IG (SIGALRM);
}