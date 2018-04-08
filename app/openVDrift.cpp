#include <stdio.h>
#include <cstdint>
#include <chrono>
#include <sstream>
#include <thread>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
//#include <opendavinci/odcore/base/Service.h>

#include "lib/cluon-complete.hpp"
#include "messages.hpp"


// VDRIFT
#include "lib/vdrift/src/vdrift.h"

using namespace std;


int main(int argc, char * argv[]) {
	std::cout << "[VDRIFT] NOT RUNNING" << std::endl;
	cluon::OD4Session od4(111,[](cluon::data::Envelope &&envelope) noexcept {
      if (envelope.dataType() == opendlv::proxy::Position::ID()) {
          opendlv::proxy::Position resPos = cluon::extractMessage<opendlv::proxy::Position>(std::move(envelope));
          std::cout << "Sent a message with the current to " << resPos.pos() << "." << std::endl;
      }
  });
	//VDrift* v = new VDrift();
	//v->run(argc,argv);
	if(od4.isRunning() == 0){
        std::cout << "[OD4] NOT RUNNING" << std::endl;
        return -1;
  }else{
		std::cout << "[OD4] RUNNING" << std::endl;
	}

	std::cout << "[OD4] SENDING POSITION [0.0,0.0,0.0,0.0]" << std::endl;
	opendlv::proxy::Position reqPos;
	reqPos.pos(0.1);
	od4.send(reqPos);

	return 0;
}
