typedef enum {
  kAllStop = 'S',
  kAheadFull = 'A',
  kAheadTwoThirds = 'B',
  kAheadOneThird = 'C',
  kBackOneThird = 'D',
  kBackTwoThirds = 'E',
  kBackFull = 'F',
  kLeft = 'G',
  kRight = 'H',
  kNoOp = 'I'
} MotionCommand;

int currentBatteryLevel;
int sonarDistanceCm = 255;
MotionCommand newCommand = kNoOp;
