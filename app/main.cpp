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

	CluonHandler* ch = new CluonHandler();
	/*if(ch->session()->isRunning()){
		std::cout << "OPENDLV RUNNING SENDING MESSAGE"<< std::endl;
		opendlv::sim::Frame reqF;
		reqF.x(0.1);
		ch->session()->send(reqF);
	}else{
		std::cout << "OPENDLV NOT RUNNING"<< std::endl;
	}*/
	std::cout << "[VDRIFT] STARTING" << std::endl;
	VDrift* v = new VDrift();
	v->run(argc,argv,ch);
	return 0;
}
