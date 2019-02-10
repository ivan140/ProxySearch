#include "ProxySearch.h"
#include <WiFiClientSecure.h>

ProxySearch::ProxySearch(){
}

ProxySearch::~ProxySearch(){
}

bool ProxySearch::checkProxyAPI()
{
	if (!p.Ping(PROXYLIST_ADDRESS)) {
		Serial.println(PROXYLIST_ADDRESS + (String)" not found!");
		if (!p.Ping("8.8.8.8"))
			Serial.println("No ping to google!");
		else {
			
		}	
	}else{
		Serial.println(PROXYLIST_ADDRESS + (String)" found!");
		return true;
	}
	return false;
}

String fetchURL(BearSSL::WiFiClientSecure *client, const char *host, const uint16_t port, const char *path) {
  client->connect(host, port);
  if (!client->connected()) {
    Serial.printf("*** Can't connect. ***\n-------\n");
    return "";
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
  return response;
}

bool ProxySearch::getProxyServer(){
	BearSSL::WiFiClientSecure client;
	client.setInsecure();
	String host = PROXYLIST_ADDRESS;
	String json = fetchURL(&client, PROXYLIST_ADDRESS, 443, ((String)"/proxy?" + (String)PROXYLIST_NOTCOUNTRY + (String)"&" + (String)PROXYLIST_COUNTRY + (String)"&protocol=http").c_str());
	DynamicJsonBuffer jsonBuffer;
	if(json != ""){
		JsonObject& root = jsonBuffer.parse(json);
		if(root.success()){
			strcpy(this->proxyIP,root["ip"].as<String>().c_str());
			strcpy(this->proxyPort, root["port"].as<String>().c_str());
		}
	}	
}

bool ProxySearch::testProxyServer(String url){
	return p.Ping(this->proxyIP);
}