#include "systemc.h"

SC_MODULE(CPU_2) {

	sc_in<bool> isDataBeingDelivered;
	sc_in<bool> clock;

	sc_out<sc_uint<16>> dataInput;
	sc_out<bool> isReading;
	sc_out<bool> reset;

	void handle();

	SC_CTOR(CPU_2) {
		SC_CTHREAD(handle, clock.pos());
		reset_signal_is(reset, true);
	}
};