#include <stdio.h>
#include <cstdint>
#include <chrono>
#include <sstream>
#include <thread>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>

#include "lib/cluon_handler.h"
#include "messages.hpp"


// VDRIFT
#include "lib/_vdrift/vdrift.h"


int main(int argc, char * argv[]) {

	std::cout << "[VDRIFT] STARTING" << std::endl;
	VDrift* v = new VDrift();
	v->run(argc,argv);
	return 0;
}
