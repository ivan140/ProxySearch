#include "ProxySearch.h"
#include "ESP8266Ping.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

ProxySearch::ProxySearch(){
	
}

ProxySearch::~ProxySearch(){
}

bool ProxySearch::checkProxyAPI()
{
	if (!Ping.ping(PROXYLIST_ADDRESS, 5)) {
		Serial.println(PROXYLIST_ADDRESS + (String)" not found!");
		if (!Ping.ping("8.8.8.8", 5))
			Serial.println("No ping to google!");
		else {
			
		}	
	}else{
		Serial.println(PROXYLIST_ADDRESS + (String)" found!");
		return true;
	}

	return false;
}

void fetchURL(BearSSL::WiFiClientSecure *client, const char *host, const uint16_t port, const char *path) {
  client->connect(host, port);
  if (!client->connected()) {
    Serial.printf("*** Can't connect. ***\n-------\n");
    return;
  }
  Serial.printf("Connected!\n-------\n");
  client->write("GET ");
  client->write(path);
  client->write(" HTTP/1.0\r\nHost: ");
  client->write(host);
  client->write("\r\nUser-Agent: ESP8266\r\n");
  client->write("\r\n");
  uint32_t to = millis() + 5000;
  while (client->connected()) {
		if(client->readStringUntil('\n') == "\r")
			break;
  }
  String response = (String)client->readStringUntil('\r');
  Serial.print(response);
  client->stop();
}

bool ProxySearch::getProxyServer(){
	BearSSL::WiFiClientSecure client;
	static const uint8_t fp[] = {0xC9,0x67,0x1D,0x3B,0x1E,0x4C,0xD6,0x3D,0x62,0x7E,0xC3,0x06,0xBE,0xD7,0xE2,0x60,0x41,0xAF,0xAB,0x76};
	client.setFingerprint(fp);
	String host = PROXYLIST_ADDRESS;
	fetchURL(&client, PROXYLIST_ADDRESS, 443, "/proxy");
}
/*
bool ProxySearch::getProxyServer1(){
	HTTPClient http;
	String url = PROXYLIST_URL + (String)"?" + PROXYLIST_NOTCOUNTRY + (String)"&" + PROXYLIST_COUNTRY;// + (String)"&" +PROXYLIST_PARAMETERS;
	Serial.println(url);
	http.begin(url,"c9671d3b1e4cd63d627ec306bed7e26041afab76");
	int httpCode = http.GET();
	Serial.println("code: " + (String)httpCode);
	if (httpCode > 0) {
		String payload = http.getString();
		Serial.println(payload);
		DynamicJsonBuffer jsonBuffer;
		JsonObject& root = jsonBuffer.parse(payload);
		return true;
	}
	return false;
}*/

bool ProxySearch::testProxyServer(String url){
	return false;
}