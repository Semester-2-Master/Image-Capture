#include <WiFi.h>
#include <WiFiAP.h>

const char *ssid = "PollenCollect";
//const char *password = "pc12345";

void init_wifi() {
  if (!WiFi.softAP(ssid)) {
    log_e("Soft AP creation failed.");
    while(1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
}
