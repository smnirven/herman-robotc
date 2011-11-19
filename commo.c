#include "constants.h"

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

MotionCommand parseCommand(char cmd)
{
  return (MotionCommand) cmd;
}

task TelemetrySender()
{
  nxtEnableHSPort();                                //Enable High Speed Port #4
  nxtSetHSBaudRate(9600);                           //Xbee Default Speed
  nxtHS_Mode = hsRawMode;                           //Set to Raw Mode (vs. Master/Slave Mode)

  while(true)
  {
    wait1Msec(1500);                                 // Allow for a short wait, freeing up the CPU for other tasks.

    nxtDisplayBigStringAt(20, 52, "%3.1f V", currentBatteryLevel / (float) 1000);

    buildTelemetryPacket();
    nxtWriteRawHS(packetToSend, 6);
    wait1Msec(1000);
  }
  return;
}

task CommandParser()
{
  ubyte incomingData;

  while(true)
  {
    if(nxtGetAvailHSBytes())                        //Check to see if we have any data coming in
	  {
		   if(nxtReadRawHS(incomingData, 1))            //Ask for the data, save to "incomingData".
		   {
		     newCommand = parseCommand((char)incomingData);
		   }
		}
		else  //No Data, Wait a little before trying again
		{
      wait1Msec(25);                                //Wait 25ms before checking again.
		}
  }
}
