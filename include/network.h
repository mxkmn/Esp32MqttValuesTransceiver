#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "_config.h"

class Network {
private:
	WiFiClient _wifiClient;
	PubSubClient _mqttClient;
	uint8_t _lastWiFiStatus = -1;

	void checkWiFiChanges();
	void reconnect();
public:
	void init(String wifiSsid, String wifiPass, String mqttHost);
	bool sendPinInfo(int* values, uint8_t sensorsCount);
	void keepInUse();
	void enableWifi(bool shouldEnable);
};