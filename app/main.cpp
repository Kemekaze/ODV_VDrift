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

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using std::chrono::system_clock;


std::atomic_bool stop(false);

void runVdrift(int argc, char * argv[], CluonHandler *ch){
	std::cout << "[VDRIFT] STARTING" << std::endl;
	VDrift* v = new VDrift();
	v->run(argc,argv,ch);
}
void runCluon(int argc, char * argv[]){
	CluonHandler* ch = new CluonHandler();
	opendlv::sim::Frame reqF;
	reqF.x(0.1);
	ch->session()->send(reqF);
}

int main(int argc, char * argv[]) {

	CluonHandler* ch = new CluonHandler();
	std::cout << "[VDRIFT] STARTING" << std::endl;
	VDrift* v = new VDrift();
	v->run(argc,argv,ch);
	/*thread tVDrift(runVdrift, argc,argv,ch);
	//thread tCluon(runCluon, argc,argv);
	string input = "";
	getline(cin, input);
	stop = true;
	//tCluon.join();
	tVDrift.join();*/
	return 0;
}
