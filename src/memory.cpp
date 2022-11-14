#include "memory.h"

void Memory::init() {
	SPIFFS.begin();
  if (!SPIFFS.exists(MEMORY_NAME_SENSORS_COUNT)) { // on first start (file not exists)
		delay(1000);
		Serial.println("Formatting... Please wait up to 10 seconds.");
    SPIFFS.format();
		setConfig(); // default config
  }
}

String Memory::readFile(String file) {
  File f = SPIFFS.open(file, "r");
  if (!f) {
    Serial.println("Error: " + file + " has not been read. \"error\" will be returned.");
    f.close();
    return("error");
  } else {
		String out = f.readStringUntil('\n');
		f.close();
		return out.substring(0, out.length()-1);
	}
}

void Memory::writeFile(String file, String data) {
  File f = SPIFFS.open(file, "w");
  if (!f) {
    Serial.println("Error: " + file + " has not been written.");
  } else {
		f.println(data);
	}
  f.close();
}

void Memory::setConfig(String wifiSsid, String wifiPass, String mqttHost, uint8_t sensorsCount, bool isNotDelayed) {
	writeFile(MEMORY_NAME_WIFI_SSID, wifiSsid);
	writeFile(MEMORY_NAME_WIFI_PASS, wifiPass);
	writeFile(MEMORY_NAME_MQTT_HOST, mqttHost);
	writeFile(MEMORY_NAME_SENSORS_COUNT, String(sensorsCount));
	writeFile(MEMORY_NAME_FAST_CLICK, String(isNotDelayed));
}

String Memory::getWifiSsid() { return readFile(MEMORY_NAME_WIFI_SSID); }
String Memory::getWifiPass() { return readFile(MEMORY_NAME_WIFI_PASS); }
String Memory::getMqttHost() { return readFile(MEMORY_NAME_MQTT_HOST); }
uint8_t Memory::getSensorsCount() { return readFile(MEMORY_NAME_SENSORS_COUNT).toInt(); }

void Memory::setFastClick(bool isNotDelayed) {
	writeFile(MEMORY_NAME_FAST_CLICK, String(isNotDelayed));
}

bool Memory::shouldSetupAp() {
	bool isNotDelayed = readFile(MEMORY_NAME_FAST_CLICK).toInt();
	return isNotDelayed || (readFile(MEMORY_NAME_WIFI_SSID) == "");
}