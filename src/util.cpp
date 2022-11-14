#include "util.h"

void Util::init() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	_memory.init();

	if (_memory.shouldSetupAp()) {
		_memory.setFastClick(false);
		delay(1000);

		SettingsAp settings;
		settings.initAp(_memory); // infinite loop here until reboot
	} else {
		delay(1000);
		_sensorsCount = _memory.getSensorsCount();
		_sensors.init(_sensorsCount);
		_network.init(_memory.getWifiSsid(), _memory.getWifiPass(), _memory.getMqttHost());
		if (_memory.getSensorsCount() > 6) {
			_network.enableWifi(false);
		}
	}
}

void Util::waitForReset() {
	_memory.setFastClick(true);
	digitalWrite(LED_BUILTIN, HIGH);

	delay(25);
	Serial.printf("\nDevice name %s. Connecting to %s...\nPushing the Reset button (EN) while the LED is lit during boot up will take the controller into configuration mode, it can be reconfigured via a device with WiFi.\n", WiFi.macAddress().c_str(), _memory.getWifiSsid());

	delay(1500);

	// if we haven't waited for an extra click:
	_memory.setFastClick(false);
	digitalWrite(LED_BUILTIN, LOW);
}

void Util::sendValuesIfNeeded() {
	time_t now = millis();
	if (_valuesSendingTime < now - (UPDATE_TIME_IN_SECONDS * 1000)) {
		_valuesSendingTime = now;

		int values[_sensorsCount];
		_sensors.setCurrentValuesToArray(values, _sensorsCount);

		if (_memory.getSensorsCount() > 6) {
			_network.enableWifi(true);
			_network.sendPinInfo(values, _sensorsCount);
			_network.enableWifi(false);
		} else {
			_network.sendPinInfo(values, _sensorsCount);
		}
	}
}

void Util::keepNetworkInUse() {
	_network.keepInUse();
}