#include "commo.c"

task main()
{
  StartTask(TelemetrySender);                             // Start Task TOne.

  while(true)
  {
    wait1Msec(300);                                 // Allow for a short wait, freeing up the CPU for other tasks.

    currentBatteryLevel = nImmediateBatteryLevel;
  }
  return;
}
