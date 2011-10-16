int currentBatteryLevel;
ubyte packetToSend[6];

void buildTelemetryPacket()
{
  packetToSend[0] = 'b';
  packetToSend[1] = 'v';
  string batteryVoltageStr;
  sprintf(batteryVoltageStr, "%u", currentBatteryLevel);
  packetToSend[2] = (ubyte) StringGetChar(batteryVoltageStr, 0);
  packetToSend[3] = (ubyte) StringGetChar(batteryVoltageStr, 1);
  packetToSend[4] = (ubyte) StringGetChar(batteryVoltageStr, 2);
  packetToSend[5] = (ubyte) StringGetChar(batteryVoltageStr, 3);
}

task TelemetrySender()
{
  nxtEnableHSPort();                                //Enable High Speed Port #4
  nxtSetHSBaudRate(9600);                           //Xbee Default Speed
  nxtHS_Mode = hsRawMode;                           //Set to Raw Mode (vs. Master/Slave Mode)

  while(true)
  {
    wait1Msec(2500);                                 // Allow for a short wait, freeing up the CPU for other tasks.

    nxtDisplayCenteredBigTextLine(3, "SENDING...");     // Display that TOne is running simultaneously with Main.
    nxtDisplayBigStringAt(20, 52, "%3.1f V", currentBatteryLevel / (float) 1000);

   buildTelemetryPacket();
    nxtWriteRawHS(packetToSend, 6);
  }
  return;
}
