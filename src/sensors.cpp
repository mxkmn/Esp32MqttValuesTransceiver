#include "sensors.h"

void Sensors::init(uint8_t sensorsCount) {
	for (uint8_t i = 0; i < sensorsCount; i++) {
		pinMode(SENSOR_PINS[i], INPUT);
	}
}

int* Sensors::setCurrentValuesToArray(int* values, uint8_t sensorsCount) {
	for (size_t i = 0; i < sensorsCount; i++) {
		values[i] = analogRead(SENSOR_PINS[i]);
	}
	return values;
}