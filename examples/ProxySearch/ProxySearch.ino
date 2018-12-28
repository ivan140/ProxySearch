#include "ProxySearch.h"

// Initialize Wifi connection to the router
const char* ssid  = SECRET_SSID;
const char* password = SECRET_PASS;

ProxySearch ps;

void setup() {
  connectToWifi();
  if(ps.checkProxyAPI()){
    if(ps.getProxyServer()){
      Serial.println("Server found.");
    }
  }
}

void loop() {


}

void connectToWifi() {
  int retries = 0;
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.persistent(false);
  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi:\n");
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED && retries < 10) {
      delay(500);
      //Serial.print(".");
      retries++;
    }
  }
}
