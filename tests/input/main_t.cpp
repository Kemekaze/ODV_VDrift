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

#include "messages.hpp"
#include "cluon-complete.hpp"

cluon::OD4Session *od4;

std::function<void(cluon::data::Envelope &&envelope)> lamda1 = [](cluon::data::Envelope &&envelope){
  std::cout << "[0][LAMDA]" << std::endl;
  opendlv::sim::scenario::Scenario si;
  od4->send(si);
};

std::function<void(cluon::data::Envelope &&envelope)> lamda2 = [](cluon::data::Envelope &&envelope){
  std::cout << "[2][LAMDA2]" << std::endl;
  opendlv::sim::scenario::Frame si;
  od4->send(si);
};




int main(int argc, char * argv[]) {

  cluon::OD4Session _od4{111};
  od4 = &_od4;
  od4->dataTrigger(opendlv::sim::scenario::Scenario::ID(), lamda1);
  od4->dataTrigger(opendlv::sim::scenario::FrameRequest::ID(), lamda2);
  while(true){
    usleep(1000000);
  }
}
