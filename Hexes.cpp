#include <systemc.h>
#include "Hexes.h"

void HEXES::displayOnHex(void) {

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

		int temp = (int) dataInput.read();

		isReading.write(0);

		if (temp < -2 && temp > 5) {
			cout << "HEX Module: Received out of range value" << endl;
		}
		else {
			if (temp == -2) {
				cout << "HEX Module: ERR" << endl;
			}
			else if (temp == -1) {
				cout << "HEX Module: Shows nothing" << endl;
			}
			else {
				cout << "HEX Module: Displaying temperature: " << programs[temp] << endl;
			}
		}
	}
}