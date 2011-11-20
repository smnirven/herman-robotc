#pragma config(Sensor, S3,     sonarSensor,         sensorSONAR)
#pragma config(Sensor, S1, GPS, sensorLowSpeed)

#include "commo.c"
#include "control.c"
#include "sonar.c"
#include "gps.c"

task main()
{
  StartTask(TelemetrySender);
  StartTask(CommandParser);
  StartTask(ControlTask);
  StartTask(SonarTask);
  StartTask(GPSTask);

  while(true)
  {
    wait1Msec(1000);                                 // Allow for a short wait, freeing up the CPU for other tasks.

    currentBatteryLevel = nImmediateBatteryLevel;
  }
  return;
}
