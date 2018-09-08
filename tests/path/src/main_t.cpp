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

  std::cout << "[1][LAMDA]" << std::endl;
  //opendlv::body::SensorInfo si;
  //od4->send(si);
  std::thread ([](){
    opendlv::sim::scenario::FrameRequest si;
    od4->send(si);
  }).detach();

};

std::function<void(cluon::data::Envelope &&envelope)> lamda2 = [](cluon::data::Envelope &&envelope){
  std::cout << "[3][LAMDA2]" << std::endl;
};
/*
  [1][LAMDA]
  [0][LAMDA]
  [1][LAMDA2]


*/



int main(int argc, char * argv[]) {

  cluon::OD4Session _od4{111};
  od4 = &_od4;
  od4->dataTrigger(opendlv::sim::scenario::Scenario::ID(), lamda1);
  od4->dataTrigger(opendlv::sim::scenario::Frame::ID(), lamda2);
  usleep(6000000);
  opendlv::sim::scenario::Scenario ci;
  ci.action(1);
  od4->send(ci);
  while(true){
    usleep(1000000);
  }
}
