#include "constants.h"

ubyte packetToSend[50];
int index;

void buildTelemetryPacket()
{
  packetToSend[0] = 'b';
  packetToSend[1] = 'v';
  string batteryVoltageStr;
  sprintf(batteryVoltageStr, "%u", currentBatteryLevel);
  string latStr;
  sprintf(latStr, "%d", currentLat);
  string lngStr;
  sprintf(lngStr, "%d", currentLng);
  index=2;
  for(int i=0;i<strlen(batteryVoltageStr);i++){
    packetToSend[index] = (ubyte) StringGetChar(batteryVoltageStr, i);
    index++;
  }
  packetToSend[index] = 'l';
  index++;
  packetToSend[index] = 'a';
  index++;
  packetToSend[index] = 't';
  index++;
  for(int i=0; i<strlen(latStr);i++){
    packetToSend[index] = (ubyte) StringGetChar(latStr, i);
    index++;
  }
  packetToSend[index] = 'l';
  index++;
  packetToSend[index] = 'n';
  index++;
  packetToSend[index] = 'g';
  index++;
  for(int i=0; i<strlen(lngStr);i++){
    packetToSend[index] = (ubyte) StringGetChar(lngStr, i);
    index++;
  }
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
    nxtDisplayBigStringAt(20, 52, "%3.1f V", currentBatteryLevel / (float) 1000);

    buildTelemetryPacket();
    nxtWriteRawHS(packetToSend, index+1);
    wait1Msec(5000);
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
