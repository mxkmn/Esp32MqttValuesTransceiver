#pragma once

#include <Arduino.h>
#include <SPIFFS.h>
#include "_config.h"

#define MEMORY_NAME_WIFI_SSID "/wifi_ssid"
#define MEMORY_NAME_WIFI_PASS "/wifi_pass"
#define MEMORY_NAME_MQTT_HOST "/mqtt_host"
#define MEMORY_NAME_SENSORS_COUNT "/sensors"
#define MEMORY_NAME_FAST_CLICK "/fast_clck"

class Memory {
private:
	String readFile(String file);
	void writeFile(String file, String data);
public:
	void init();
	void setConfig(String wifiSsid = "", String wifiPass = "", String mqttHost = "", uint8_t sensorsCount = 6, bool isNotDelayed = false);

	String getWifiSsid();
	String getWifiPass();
	String getMqttHost();
	uint8_t getSensorsCount();

	void setFastClick(bool isNotDelayed);
	bool shouldSetupAp();
};