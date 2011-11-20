#include "drivers/DGPS-driver.h"
#include "constants.h"

task GPSTask() {
  while(true){
    currentLat = DGPSreadLatitude(GPS);     // Lat will be in decimal degrees
    currentLng = DGPSreadLongitude(GPS);      // Lon will be in decimal degrees
    gpsLinkStatus = DGPSreadStatus(GPS);
    wait1Msec(1000);
  }
}
