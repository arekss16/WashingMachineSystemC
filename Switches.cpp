#include <systemc.h>
#include "Switches.h"

void SWITCHES::clear(void) {
	system("cls");
}

int SWITCHES::readUserInput(void) {
	int result;
	while (!(cin >> result)) {
		cin.clear();
		cin.ignore();
		cout << "Incorrect choice";
	}
	return result;
}

void SWITCHES::sendInput(int userInput) {
	wait();
	isSending.write(1);
	input.write(userInput);
	wait();
}

void SWITCHES::closeSendingOutput(void) {
	wait();
	isSending.write(0);
	wait();
}

void SWITCHES::read(void) {
	int processed = 1;
	
	while (true) {
		if (processed == 1) {
			int userInput = readUserInput();

			clear();

			sendInput(userInput);
		}

		closeSendingOutput();

		processed = isProcessed.read();
	}
}
