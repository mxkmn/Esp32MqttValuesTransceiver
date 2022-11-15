#pragma once

#include "_config.h"
#include <Arduino.h>

class Sensors {
public:
	void init(uint8_t sensorsCount);
	int* setCurrentValuesToArray(int* values, uint8_t sensorsCount);
};