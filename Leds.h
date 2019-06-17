#include <systemc.h>

SC_MODULE(LEDS) {
	
	sc_in<bool> isDataBeingDelivered;
	sc_in<bool> clock;

	sc_out<sc_int<16>> dataInput;
	sc_out<bool> isReading;
	sc_out<bool> reset;

	int activeId;

	void displayOnLed();

	SC_CTOR(LEDS) {
		SC_CTHREAD(displayOnLed, clock.pos());
		reset_signal_is(reset, true);
	}

};
