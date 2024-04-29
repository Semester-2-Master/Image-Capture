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

void get_time(char* timeBuffer, size_t bufferSize) {
  struct tm timeinfo;
  
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    if (timeBuffer != nullptr && bufferSize > 0) {
      timeBuffer[0] = '\0'; // Set empty string if time retrieval fails
    }
    return;
  }

  // Format the time into the provided buffer
  strftime(timeBuffer, bufferSize, "%B: %d-%Y %H:%M:%S", &timeinfo);
}

void init_time() {
  Serial.println("time init");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  //printLocalTime();
  Serial.println("time init done");
}

