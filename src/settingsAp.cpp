#include "settingsAp.h"

void SettingsAp::sendHtml() { // sending an HTML page with the settings to the device
	String concatStr;
	concatStr += FPSTR(settingsPage1);
	concatStr += "wifi = '"; concatStr += _memory.getWifiSsid(); concatStr += "'";
	if (_memory.getWifiSsid() != "") {
		concatStr += ", mqtt = '"; concatStr += _memory.getMqttHost();
		concatStr += "', type = "; concatStr += _memory.getSensorsCount();
	}
	concatStr += ";";
	concatStr += FPSTR(settingsPage2);

	_server.send(200, "text/html", concatStr); // send to device
}

void SettingsAp::getData() { // getting POST from a smart device and saving data with a reboot
	String val, ssid, pass, mqtt; int type;
	for (int i = 0; i <= _server.args(); i++) {
		val = _server.arg(i);
		switch (i) {
		case 0: {
			ssid = (val != "") ? val : _memory.getWifiSsid();
		} break;
		case 1: {
			pass = (val != "") ? val : _memory.getWifiPass();
		} break;
		case 2: {
			mqtt = (val != "") ? val : _memory.getMqttHost();
		} break;
		case 3: {
			type = (val != "") ? val.toInt() : _memory.getSensorsCount();
		} break;

		default: {
			Serial.printf("Error: so much args (%d), %dth is %s\n", _server.args(), i+1, val);
		} break;
		}
	}
	_memory.setConfig(ssid, pass, mqtt, type);

	_server.send(204, "");
	ESP.restart();
}

void SettingsAp::initAp(Memory& memory) { // setting up the access point to configure
	_memory = memory;

	WiFi.mode(WIFI_AP); WiFi.softAP(AP_NAME);
	Serial.printf("\nTo set up, connect to an access point \"%s\" and go to \"%s\" in browser...\n", AP_NAME, WiFi.softAPIP().toString());

	_server.on("/", std::bind(&SettingsAp::sendHtml, this));
	_server.on("/senddata", std::bind(&SettingsAp::getData, this));
	_server.begin();

	uint16_t timeCounter = 0;
	while (true) {
		digitalWrite(LED_BUILTIN, timeCounter / 25);
		_server.handleClient();
		timeCounter = (timeCounter+1)%50;
		delay(10);
	}
}