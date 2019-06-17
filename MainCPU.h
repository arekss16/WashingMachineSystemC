#include <sstream>
#include <string>
#include "systemc.h"
#include "list"

using namespace std;

SC_MODULE(CPU_1) {
	sc_in<bool> clock;
	sc_in<bool> reset;
	sc_in<sc_uint<16>> inputData;
	sc_out<sc_uint<16>> outputDataCpu2;
	sc_out<sc_int<16>> outputHexDisplayData;
	sc_out<sc_int<16>> outputLedsDisplayData;
	sc_in<bool> isSwitchSending;
	sc_in<bool> areLedsReading;
	sc_in<bool> areHexesReading;
	sc_in<bool> isCpu2Reading;
	sc_out<bool> isSwitchDataProcessed;
	sc_out<bool> isSendingToHex;
	sc_out<bool> isSendingToLeds;
	sc_out<bool> isSendingToCpu2;
	
	const int programs[6] = { 30, 35, 40, 60, 80, 90 }; 
	int activeSwitches[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
	int activeProgramId = -1;
	bool isError = false; 
	int processing = 0;
	bool isProcessed = false;
	
	void launchProgram(int id);
	
	void display(string ledsLine, string switchesLine, string hexPanel);

	void printWasher(int programId, bool isError);
	
	int countActiveProgramSwitches();

	string getSwitchesNames(int rangeFrom, int rangeTo);
	
	string getActiveProgramSwitches();
	
	string getActiveAllSwitches();
	
	int getActiveSwitch();
	
	void sendToPeripherals(int value);

	void manageState();

	void toggle(int inputData);

	void handle();

	void showError();

	void turnOff();

	void processData(int switchNumber);
	
	void launchProgram1();
	
	void launchProgram2();
	
	void launchProgram3();
	
	void launchProgram4();
	
	void launchProgram5();

	SC_CTOR(CPU_1) {
		SC_CTHREAD(handle, clock.pos());
		SC_CTHREAD(launchProgram1, clock.pos());
		SC_CTHREAD(launchProgram2, clock.pos());
		SC_CTHREAD(launchProgram3, clock.pos());
		SC_CTHREAD(launchProgram4, clock.pos());
		SC_CTHREAD(launchProgram5, clock.pos());
		reset_signal_is(reset, true);
	}
};
