#include "systemc.h"
#include "Switches.h"
#include "SecondaryCPU.h"
#include "MainCPU.h"
#include "Leds.h"
#include "Hexes.h"

SC_MODULE(SYSTEM) {
	CPU_1* cpu1;
	CPU_2* cpu2;
	LEDS* leds;
	HEXES* hexes;
	SWITCHES* switches;

	sc_signal<bool> resetSignal;
	sc_clock clockSignal;
	sc_signal<sc_uint<16>> switchesData{ "switchesData" };
	sc_signal<sc_int<16>> hexDisplayData{ "hexDisplayData" };
	sc_signal<sc_int<16>> ledsDisplayData{ "ledsDisplayData" };
	sc_signal<sc_uint<16>> cpu2Data{ "cpu2Data" };

	sc_signal<bool> switchesSendingSignalToCpu;
	sc_signal<bool> cpuProcessSwitchesState;

	sc_signal<bool> cpuSendingToHex;
	sc_signal<bool> cpuSendingToLeds;
	sc_signal<bool> cpu1SendingToCpu2;
	sc_signal<bool> cpu2ReadingCpu1Data;
	sc_signal<bool> ledsReadingCpuData;
	sc_signal<bool> hexesReadingCpuData;

	SC_CTOR(SYSTEM) : clockSignal("clockSignal", 500, SC_NS) { // 500 nano sekund
		cpu2 = new CPU_2("cpu2");
		cpu1 = new CPU_1("cpu1");
		switches = new SWITCHES("sw");
		leds = new LEDS("leds");
		hexes = new HEXES("hexes");

		cpu1->clock(clockSignal);
		cpu1->inputData(switchesData);
		cpu1->reset(resetSignal);
		cpu1->outputDataCpu2(cpu2Data);
		cpu1->outputHexDisplayData(hexDisplayData);
		cpu1->outputLedsDisplayData(ledsDisplayData);
		cpu1->isSendingToHex(cpuSendingToHex);
		cpu1->isSendingToLeds(cpuSendingToLeds);
		cpu1->isSendingToCpu2(cpu1SendingToCpu2);
		cpu1->areHexesReading(hexesReadingCpuData);
		cpu1->areLedsReading(ledsReadingCpuData);
		cpu1->isCpu2Reading(cpu2ReadingCpu1Data);
		cpu1->isSwitchSending(switchesSendingSignalToCpu);
		cpu1->isSwitchDataProcessed(cpuProcessSwitchesState);

		cpu2->clock(clockSignal);
		cpu2->dataInput(cpu2Data);
		cpu2->reset(resetSignal);
		cpu2->isDataBeingDelivered(cpu1SendingToCpu2);
		cpu2->isReading(cpu2ReadingCpu1Data);

		switches->clock(clockSignal);
		switches->input(switchesData);
		switches->reset(resetSignal);
		switches->isSending(switchesSendingSignalToCpu);
		switches->isProcessed(cpuProcessSwitchesState);

		leds->clock(clockSignal);
		leds->dataInput(ledsDisplayData);
		leds->reset(resetSignal);		
		leds->isDataBeingDelivered(cpuSendingToLeds);
		leds->isReading(ledsReadingCpuData);

		hexes->clock(clockSignal);
		hexes->dataInput(hexDisplayData);
		hexes->reset(resetSignal);
		hexes->isDataBeingDelivered(cpuSendingToHex);
		hexes->isReading(hexesReadingCpuData);
	}

	~SYSTEM() {
		delete cpu1;
		delete cpu2;
		delete switches;
		delete leds;
		delete hexes;
	}
};

int sc_main(int argc, char* argv[]);