#include "network.h"

void Network::init(String wifiSsid, String wifiPass, String mqttHost) {
	// shitty C++ conversions from String to char[]
	uint8_t wifiSsidLength = wifiSsid.length()+1; char wifiSsidChars[wifiSsidLength]; wifiSsid.toCharArray(wifiSsidChars, wifiSsidLength);
	uint8_t wifiPassLength = wifiPass.length()+1; char wifiPassChars[wifiPassLength]; wifiPass.toCharArray(wifiPassChars, wifiPassLength);
	uint8_t mqttHostLength = mqttHost.length()+1; char mqttHostChars[mqttHostLength]; mqttHost.toCharArray(mqttHostChars, mqttHostLength);

	WiFi.mode(WIFI_STA); // switch to client mode
	WiFi.begin(wifiSsidChars, wifiPassChars); // init the connection
	WiFi.waitForConnectResult();

	_mqttClient.setClient(_wifiClient);
	_mqttClient.setServer(mqttHostChars, 1883);
}

void Network::enableWifi(bool shouldEnable) {
	if (shouldEnable) {
		WiFi.mode(WIFI_MODE_STA);
		WiFi.begin();
		WiFi.waitForConnectResult();
	} else {
		WiFi.disconnect();
		WiFi.mode(WIFI_OFF);
		delay(500);
	}
}

void Network::reconnect() {
	while (!_mqttClient.connected()) {
		Serial.print("Connecting via MQTT to the server...");
		if (_mqttClient.connect("arduino_client")) {
			Serial.println(" Connected!");
		} else {
			Serial.printf(" Not connected, error rc%d, reconnect after 2 seconds...\n", _mqttClient.state());
			digitalWrite(LED_BUILTIN, HIGH);
			delay(1500);
			digitalWrite(LED_BUILTIN, LOW);
			delay(500);
		}
	}
}

bool Network::sendPinInfo(int* values, uint8_t sensorsCount) {
	String message = "";

	for (uint8_t i = 0; i < sensorsCount; i++) {
		message += String(i) + " " + String(values[i]) + '\n';
	}

	if (!_mqttClient.connected()) {
		reconnect();
	}
	_mqttClient.publish(WiFi.macAddress().c_str(), message.c_str());
	Serial.print(message.c_str()); // for debug

	return false;
}

void Network::keepInUse() {
	checkWiFiChanges();
	if (_mqttClient.connected()) {
		_mqttClient.loop();
	}
}

void Network::checkWiFiChanges() { // shows changes in WiFi status
	if (WiFi.status() != _lastWiFiStatus) {
		_lastWiFiStatus = WiFi.status();
		Serial.print("New WiFI status: ");
		switch (_lastWiFiStatus) {
			case WL_CONNECTED: { Serial.println("WL_CONNECTED"); return; }
			case WL_IDLE_STATUS: { Serial.println("WL_IDLE_STATUS (in process of changing between statuses)"); return; }
			case WL_DISCONNECTED: { Serial.println("WL_DISCONNECTED"); return; }
			case WL_CONNECTION_LOST: { Serial.println("WL_CONNECTION_LOST"); return; }
			case WL_CONNECT_FAILED: { Serial.println("WL_CONNECT_FAILED"); return; }
			case WL_NO_SSID_AVAIL: { Serial.println("WL_NO_SSID_AVAIL"); return; }
			case WL_SCAN_COMPLETED: { Serial.println("WL_SCAN_COMPLETED"); return; }
			case WL_NO_SHIELD: { Serial.println("WL_NO_SHIELD"); return; }
			default: { Serial.println("Unknown"); return; }
		}
	}
}