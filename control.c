#include "constants.h"

void processNewCommand(MotionCommand cmd){
  switch(cmd){
    case kAllStop:
      motor[motorC] = 0;
      motor[motorA] = 0;
      PlaySound(soundException);
      break;
    case kAheadFull:
      motor[motorC] = 100;
      motor[motorA] = 100;
      PlaySound(soundBeepBeep);
      break;
    case kAheadTwoThirds:
      motor[motorC] = 66;
      motor[motorA] = 66;
      break;
    case kAheadOneThird:
      motor[motorC] = 33;
      motor[motorA] = 33;
      break;
    case kBackOneThird:
      motor[motorC] = -33;
      motor[motorA] = -33;
      break;
    case kBackTwoThirds:
      motor[motorC] = -66;
      motor[motorA] = -66;
      break;
    case kBackFull:
      motor[motorC] = -100;
      motor[motorA] = -100;
      PlaySound(soundFastUpwardTones);
      break;
    case kLeft:
      motor[motorC] = 66;
      motor[motorA] = -66;
      break;
    case kRight:
      motor[motorC] = -66;
      motor[motorA] = 66;
      break;
  }
}

task ControlTask()
{
  while(true) {
    if(newCommand != kNoOp) {
      processNewCommand(newCommand);
      newCommand=kNoOp;
    }
    wait1Msec(250);
  }

  return;
}
