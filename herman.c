#pragma config(Sensor, S3,     sonarSensor,         sensorSONAR)

#include "commo.c"
#include "control.c"
#include "sonar.c"

task main()
{
  StartTask(TelemetrySender);
  StartTask(CommandParser);
  StartTask(ControlTask);
  StartTask(SonarTask);

  while(true)
  {
    wait1Msec(300);                                 // Allow for a short wait, freeing up the CPU for other tasks.

    currentBatteryLevel = nImmediateBatteryLevel;
  }
  return;
}
