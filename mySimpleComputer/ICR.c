#include <mySimpleComputer/sc_variables.h>
#include <signal.h>
#include <sys/time.h>

static int forceTick = 0;
static int skippingTicks = 0;

void
ICR (int signo)
{
  if (signo == SIGUSR1)
    {
      CU (signo);
      return;
    }

  tickCommandStage = 0;
  sc_regGet (REG_TICK_IGNORE, &skippingTicks);

  if (skippingTicks && !forceTick)
    {
      if (isRunningVar == 1)
        sc_notifyListener (STATE_IS_RUNNING, sc_isRunning ());
      isRunningVar = 0;
      return;
    }

  if (isRunningVar == 0)
    sc_notifyListener (STATE_IS_RUNNING, sc_isRunning ());
  isRunningVar = 1;

  tickCounter++;

  sc_notifyListener (STATE_TICK, idleIncounter);

  if (idleIncounter > 0)
    {
      isIdleJustCompleted = 1;
      idleIncounter--;
      sc_notifyListener (STATE_INCOUNTER_UPDATE, idleIncounter);
      sc_notifyListener (STATE_POST_TICK, idleIncounter);
      if (idleIncounter > 0)
        return;
      commandStage++;
    }

  CU (SIGALRM);

  if (idleIncounter == 0)
    forceTick = 0;

  sc_notifyListener (STATE_POST_TICK, idleIncounter);

  isIdleJustCompleted = 0;
}

void
ICR_tick ()
{
  forceTick = 1;
}