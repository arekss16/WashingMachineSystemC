#include <systemc.h>

SC_MODULE(HEXES) {
	
	sc_in<bool> isDataBeingDelivered;
	sc_in<bool> clock;

	sc_out<sc_int<16>> dataInput;
	sc_out<bool> isReading;
	sc_out<bool> reset;

	const int programs[6] = { 30, 35, 40, 60, 80, 90 };
	int activeId;

	void displayOnHex();

	SC_CTOR(HEXES) {
		SC_CTHREAD(displayOnHex, clock.pos());
		reset_signal_is(reset, true);
	}

};
