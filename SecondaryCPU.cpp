#include <systemc.h>
#include "SecondaryCPU.h"

void CPU_2::handle(void) {

	isReading.write(0);

	wait(); 

	while (true) {

		isReading.write(1);

		do {
			wait();
		} while (!isDataBeingDelivered.read());

		int id = (int)dataInput.read();

		isReading.write(0);

		if (id == 5) {
			cout << "CPU_2: Received data from CPU_1" << endl;
			cout << "CPU_2: Executing program number 6 (id = " << id << ")\n";
		}
	}
}