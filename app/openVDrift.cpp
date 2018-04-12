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

#include "lib/cluon-complete.hpp"
#include "messages.hpp"


// VDRIFT
#include "lib/_vdrift/vdrift.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using std::chrono::system_clock;


std::atomic_bool stop(false);

void runVdrift(int argc, char * argv[]){
	std::cout << "[VDRIFT] STARTING" << std::endl;
	VDrift* v = new VDrift();
	v->run(argc,argv);
}
void runCluon(int argc, char * argv[]){
	cluon::OD4Session od4(111,[](cluon::data::Envelope &&envelope) noexcept {
      if (envelope.dataType() == opendlv::proxy::Position::ID()) {
          opendlv::proxy::Position resPos = cluon::extractMessage<opendlv::proxy::Position>(std::move(envelope));
          std::cout << "Sent a message with the current to " << resPos.pos() << "." << std::endl;
      }
  });
	if(od4.isRunning() != 0){
		std::cout << "[OD4] RUNNING" << std::endl;
	}
	while(od4.isRunning() != 0 && !stop){
		std::cout << "[OD4] SENDING POSITION" << std::endl;
		opendlv::proxy::Position reqPos;
		reqPos.pos(0.1);
		od4.send(reqPos);
		sleep_until(system_clock::now() + 1s);
	}
  std::cout << "[OD4] STOPPED" << std::endl;
}

int main(int argc, char * argv[]) {



	thread tVDrift(runVdrift, argc,argv);
	thread tCluon(runCluon, argc,argv);
	string input = "";
	getline(cin, input);
	stop = true;
	tCluon.join();
	tVDrift.join();

	return 0;
}
