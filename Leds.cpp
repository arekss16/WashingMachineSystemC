#include <systemc.h>
#include "Leds.h"

void LEDS::displayOnLed(void) {

	// INPUT VALUES:
	// -2 -> ERROR
	// -1 -> RESET
	// <0,5> -> PROGRAMS
	// OTHER VALUES -> IGNORE

	isReading.write(0);

	wait();

	while (true) {

		isReading.write(1);

		do {
			wait();
		} while (!isDataBeingDelivered.read());

		int temp = (int)dataInput.read();

		isReading.write(0);

		if (temp < -2 && temp > 5) {
			cout << "LEDS Module: Received out of range value" << endl;
		}
		else {
			if (temp == -2) {
				cout << "LEDS Module: All leds are off. Only LED_9 light's on" << endl;
			}
			else if (temp == -1) {
				cout << "LEDS Module: All leds are off" << endl;
			}
			else {
				cout << "LEDS Module: Only LED_: " << temp << " light's on" << endl;
			}
		}
	}
}