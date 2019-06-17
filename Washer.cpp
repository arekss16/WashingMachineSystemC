#include "systemc.h"
#include "Washer.h"

SYSTEM* top_module = NULL;

int sc_main(int argc, char* argv[]) {

	cout << "WASHING MACHINE STARTED" << endl;

	top_module = new SYSTEM("top_module");
	sc_start();

	cout << "WASHING MACHINE TURNED OFF" << endl;

    return(0);
}