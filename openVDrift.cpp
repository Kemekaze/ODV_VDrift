#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vdrift/tools/modelconvert/main.cpp>

// include vdrift packages here ...

using namespace std;

int startVdrift() {

	int result = system("/usr/games/masterthesis/vdrift/build/./vdrift");
	return result;
}
int main () {

	int value = 0;
	value = startVdrift();
	// value = test ();
}

// fix with scons compilation
// anropa funktioner ifrån VDrift
// sätta ihop VDrift med våran kod
