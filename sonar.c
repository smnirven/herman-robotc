#include "constants.h"

task SonarTask() {
  while(true) {
    sonarDistanceCm = SensorValue[sonarSensor];
    nxtDisplayBigStringAt(20, 22, "%i cm", sonarDistanceCm);
    if(sonarDistanceCm <= 30) {
      motor[motorC] = 0;
      motor[motorA] = 0;
      PlaySound(soundShortBlip);
    }
    wait1Msec(50);
  }
}
