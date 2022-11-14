#include <Arduino.h>
#include "util.h"

Util util;

void setup() {
	util.init();
	util.waitForReset();
}

void loop() {
	util.sendValuesIfNeeded();
	util.keepNetworkInUse();
}