#include <fcntl.h>
#include <include/mySimpleComputer.h>
#include <signal.h>
#include <sys/time.h>

static int tickDelaySec = 0;
static int tickDelayUsec = 500000;

static struct itimerval nval
    = { .it_interval = { 0, 500000 }, .it_value = { 0, 500000 } },
    oval;

void
IG (int signo)
{
  ICR (signo);

  nval.it_interval.tv_usec = tickDelayUsec;
  nval.it_interval.tv_sec = tickDelaySec;
  nval.it_value.tv_usec = tickDelayUsec;
  nval.it_value.tv_sec = tickDelaySec;

  setitimer (ITIMER_REAL, &nval, &oval);
}

void
IG_init ()
{
  signal (SIGALRM, IG);
  signal (SIGUSR1, IG);
  IG (SIGALRM);
}

void
IG_setTickDelay (int delaySec, int delayUsec)
{
  tickDelaySec = delaySec;
  tickDelayUsec = delayUsec;
}