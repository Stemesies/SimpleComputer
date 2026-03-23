#include "mySimpleComputer/sc_variables.h"
#include <include/mySimpleComputer.h>
#include <signal.h>
#include <sys/time.h>

static int forceTick = 0;
static int skippingTicks = 0;
static int flags = 0;
static int lastFlags = 0;
void
ICR (int signo)
{
  if (signo == SIGUSR1)
    {
      CU (signo);
      return;
    }

  sc_regGet (REG_TICK_IGNORE, &skippingTicks);
  sc_regGet (REG_ALL, &lastFlags);

  if (skippingTicks && !forceTick)
    return;

  incrementTickCounter ();

  sc_notifyListener (STATE_TICK, getIdleIncounter ());

  if (getIdleIncounter () > 0)
    {
      setIsJustIdleCompleted (1);
      decrementIdleIncounter ();
      sc_notifyListener (STATE_INCOUNTER_UPDATE, getIdleIncounter ());
      sc_notifyListener (STATE_POST_TICK, getIdleIncounter ());
      if (getIdleIncounter () > 0)
        return;
    }

  CU (signo);

  if (getIdleIncounter () == 0)
    forceTick = 0;

  sc_notifyListener (STATE_POST_TICK, getIdleIncounter ());

  sc_regGet (REG_ALL, &flags);
  if (flags != lastFlags)
    sc_notifyListener (STATE_FLAG_UPDATE, 0);

  setIsJustIdleCompleted (0);
}

void
ICR_tick ()
{
  forceTick = 1;
}