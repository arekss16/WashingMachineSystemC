#include <sstream>
#include <string>
#include "systemc.h"
#include "list"
#include "MainCPU.h"

using namespace std;

void CPU_1::launchProgram(int id) {
		while (true) {
			wait(4);
			if (id < 5 && CPU_1::processing == id && CPU_1::isProcessed) {
				cout << "CPU_1: Launching program number " << (id + 1) << " (id = " << id << ")\n";
			} 
		}
	}

void CPU_1::display(string ledsLine, string switchesLine, string hexPanel) {
	cout << "____________________________________________" << endl;
	cout << ledsLine << endl;
	cout << "|L:| 09| 08| 07| 06| 05| 04| 03| 02| 01| 00|" << endl;
	cout << "|------------------------------------------|" << endl;
	cout << hexPanel << endl;
	cout << "|------------------------------------------|" << endl;
	cout << switchesLine << endl;
	cout << "|SW| 09| 08| 07| 06| 05| 04| 03| 02| 01 |00|" << endl;
	cout << "|                __________                |" << endl;
	cout << "|               /          \\               |" << endl;
	cout << "|              /            \\              |" << endl;
	cout << "|             /              \\             |" << endl;
	cout << "|             |              |             |" << endl;
	cout << "|             \\              /             |" << endl;
	cout << "|              \\            /              |" << endl;
	cout << "|               \\__________/               |" << endl;
	cout << "\\__________________________________________/" << endl;
}

void CPU_1::printWasher(int programId, bool isError) {
		std::stringstream swStrm;
		std::stringstream ledsStrm;
		std::stringstream hexStrm;

		swStrm << "|SW|";
		ledsStrm << "|L:|";
		hexStrm << "|                                   HEX:";

		if (isError) {
			hexStrm << "ERR|";
			ledsStrm << " ON| OF| OF| OF| OF| OF| OF| OF| OF| OF|";

			for (int i = 9; i >= 0; i--) {
				if (activeSwitches[i] <= 0) {
					swStrm << "OFF|";
				}
				else {
					swStrm << " ON|";
				}
			}
		} else {
			
			ledsStrm << "OFF|OFF|OFF|OFF|";

			if (programId > -1 && programId < 6) {
				int temp = programs[programId];
				hexStrm << " " << temp << "|";
			} else {
				hexStrm << "   |";
			}

			for (int i = 9; i >= 0; i--) {
				if (activeSwitches[i] <= 0) {
					swStrm << "OFF|";
				} else {
					swStrm << " ON|";
				}
			}

			for (int i = 5; i > -1; i--) {
				if (activeSwitches[i] <= 0) {
					ledsStrm << "OFF|";
				} else {
					ledsStrm << " ON|";
				}
			}
		}		

		display(ledsStrm.str(), swStrm.str(), hexStrm.str());
	}

int CPU_1::countActiveProgramSwitches(void) {
		int active = 0;

		for (int i = 0; i < 6; i++) {
			if (activeSwitches[i] == 1) {
				active++;
			}
		}

		return active;
	}

string CPU_1::getSwitchesNames(int rangeFrom, int rangeTo) {
		std::stringstream ss;
		ss << "[ ";

		for (int i = rangeFrom; i < rangeTo; i++) {
			if (activeSwitches[i] == 1) {
				ss << "SW_" << i << ", ";
			}
		}

		ss.seekp(-2, std::ios_base::end);
		ss << " ]";

		return ss.str();
	}

string CPU_1::getActiveProgramSwitches(void) {
		return CPU_1::getSwitchesNames(0, 6);
	}

string CPU_1::getActiveAllSwitches(void) {
		return CPU_1::getSwitchesNames(0, 10);
	}

int CPU_1::getActiveSwitch(void) {
		for (int i = 0; i < 6; i++) {
			if (activeSwitches[i] == 1) {
				return i;
			}
		}
		return -1;
	}

void CPU_1::showError(void) {
	cout << "Error: More then one switch from range (SW_0 - SW_5) active! " << endl;
	cout << getActiveProgramSwitches() << endl;
	sendToPeripherals(-2); 
}

void CPU_1::processData(int switchNr) {
	isProcessed = true;
	processing = switchNr;

	if (switchNr == 5) {
		cout << "CPU_1: Sending Data to CPU_2" << endl;

		isSendingToCpu2.write(1);

		outputDataCpu2.write(switchNr);

		do {
			wait();
		} while (!isCpu2Reading.read());

		isSendingToCpu2.write(0);

		wait();
	}	
}

void CPU_1::turnOff(void) {

}

void CPU_1::toggle(int inputData) {
	if (activeSwitches[inputData] == 1) {
		activeSwitches[inputData] = 0;
	} else {
		activeSwitches[inputData] = 1;
	}
}

void CPU_1::sendToPeripherals(int value) {
	isSendingToLeds.write(1);

	outputLedsDisplayData.write(value);

	do {
		wait();
	} while (!areLedsReading.read());

	isSendingToLeds.write(0);

	isSendingToHex.write(1);

	outputHexDisplayData.write(value);

	do {
		wait();
	} while (!areHexesReading.read());

	isSendingToHex.write(0);
}

void CPU_1::manageState(void) {

	int active = countActiveProgramSwitches();

	if (active > 1) {
		isError = true;
		showError();
	} else {

		int switchNr = getActiveSwitch();

		if (switchNr >= 0) {
			activeProgramId = switchNr;
			processData(switchNr);
			sendToPeripherals(activeProgramId);
		}
		else {
			sendToPeripherals(-1);
			activeProgramId = -1;
		}
	}
}

void CPU_1::handle(void) {
		printWasher(-1, false);

		int data;
		int previousProgramID;
		bool wasErrorPreviously;

		while(true)	{
			wasErrorPreviously = isError;
			previousProgramID = activeProgramId;
			isSwitchDataProcessed.write(0);
			isProcessed = false;
			isError = false;
			activeProgramId = -1;

			if (isSwitchSending.read() == 1) {
				
				data = (int) inputData.read();
				
				if (data >= 0 && data <= 9) {
					toggle(data);
					manageState();
				} else {
					isError = wasErrorPreviously;
					activeProgramId = previousProgramID;
					manageState();
				}
				wait();
				isSwitchDataProcessed.write(1);
				printWasher(activeProgramId, isError);
			}
			wait();			
		}
	}

void CPU_1::launchProgram1(void) {
	CPU_1::launchProgram(0);
	}
void CPU_1::launchProgram2(void) {
	CPU_1::launchProgram(1);
	}
void CPU_1::launchProgram3(void) {
	CPU_1::launchProgram(2);
	}
void CPU_1::launchProgram4(void) {
	CPU_1::launchProgram(3);
	}
void CPU_1::launchProgram5(void) {
		CPU_1::launchProgram(4);
}