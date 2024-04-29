#include <WiFi.h>
#include "time.h"
#include "wifi_client.h"

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;


void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void init_time() {
  Serial.println("time initt");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
}

