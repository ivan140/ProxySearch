#pragma once
#ifndef PROXYSEARCH
#define PROXYSEARCH

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Pinger.h>

//Please define here a ProxyList API and its parameters
#define PROXYLIST_ADDRESS "api.getproxylist.com"
#define PROXYLIST_URL "https://api.getproxylist.com/proxy"
#define PROXYLIST_NOTCOUNTRY "notCountry=RU"
#define PROXYLIST_COUNTRY "country=DK"
#define PROXYLIST_PARAMETERS ""
#define DNS_SERVER "8.8.8.8"

class ProxySearch
{
public: 
	ProxySearch();
	~ProxySearch();
	char proxyIP[16];
	char proxyPort[7];
	Pinger p;
	
	bool checkProxyAPI();
	bool getProxyServer();
	bool testProxyServer(String url);
};

#endif