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
#include <SDL2/SDL.h>
#include <unistd.h>

#include "messages.hpp"
#include "cluon-complete.hpp"

#define DELAY 0
#define STEERING 1
#define ACCELERATION 2

int main(int argc, char * argv[]) {
  uint16_t cid = 111;
  std::string path = "/tests/path/paths/";
  cluon::OD4Session od4(cid,[](cluon::data::Envelope &&envelope) {

  });
  opendlv::proxy::GroundSteeringRequest steer;
  opendlv::proxy::GroundAccelerationRequest acc;
  opendlv::proxy::GroundDecelerationRequest dec;
  steer.groundSteering(0.0);
  acc.groundAcceleration(0.0);
  dec.groundDeceleration(0.0);


  std::ifstream file;
  file.open(path+"path_1.path");
  int num_lines;
  std::cout << "FILE: path_1.path" << std::endl;
  if (file.is_open()){
    for(std::string line; std::getline(file, line); ){
    std::stringstream   linestream(line);
    std::string         value;
    int index = 0;
    std::cout << "LINE: "+index << std::endl;
    while(getline(linestream,value,',')){
      float v = (float) std::stof (value);
      switch(index){
        case DELAY:{
            std::cout << "[PATH][DELAY]" << v << "\n";
            unsigned int d = (unsigned int) (v*1000000);
            usleep(d);
          }
          break;
        case STEERING:{
            steer.groundSteering(v);
            od4.send(steer);
          }
          break;
        case ACCELERATION:{
            if(v >0){
              acc.groundAcceleration(v);
              od4.send(acc);
            }else{
              dec.groundDeceleration(v);
              od4.send(dec);
            }
          }
          break;
      }
      index++;
    }
    num_lines++;
  }
  }else{
    std::cout << "FILE NOT FOUND" << std::endl;
  }


	return 0;
}
