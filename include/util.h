#pragma once

#include <Arduino.h>
#include "_config.h"
#include "memory.h"
#include "network.h"
#include "settingsAp.h"
#include "sensors.h"

class Util {
private:
	time_t _valuesSendingTime = 0;
	Memory _memory;
	Network _network;
	Sensors _sensors;
	uint8_t _sensorsCount = 6;
public:
	void init();
	void waitForReset();
	void sendValuesIfNeeded();
	void keepNetworkInUse();
};