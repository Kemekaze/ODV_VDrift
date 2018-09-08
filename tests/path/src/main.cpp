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
#include <mutex>
#include <queue>

#include "messages.hpp"
#include "cluon-complete.hpp"

#include "test_scenario.h"

/*
#define DELAY 0
#define STEERING 1
#define ACCELERATION 2
#define ERROR_ID 3
#define ERROR_VALUE 4

std::string base_path = "/tests/path/paths/";
std::string base_path_out = "/runs/";

std::queue<opendlv::sim::scenario::Scenario> scenarios;
std::mutex mu_scenario;
std::mutex mu_od4;
cluon::OD4Session *od4;

int runScenario(const int s_id,const int r_id);

std::function<void(cluon::data::Envelope &&envelope)> scenario_event = [&](cluon::data::Envelope &&envelope){
  mu_od4.lock();

  opendlv::sim::scenario::Scenario scenario = cluon::extractMessage<opendlv::sim::scenario::Scenario>(std::move(envelope));
  if(scenario.scenario() == scenarios.front().scenario()){
    switch(scenario.action()){
      case 2:{
          if(mu_scenario.try_lock()){
            std::thread (runScenario,scenario.scenario(),scenario.run()).detach();
            mu_scenario.unlock();
          }
        }
        break;
      case 4 :{
          scenarios.pop();
          if(scenarios.size() > 0){
            opendlv::sim::scenario::Scenario next_scenario = scenarios.front();
            usleep(5000000);
            od4->send(next_scenario);
          }
        }
        break;
    }
  }
  mu_od4.unlock();
};

std::function<void(cluon::data::Envelope &&envelope)> frame_event = [](cluon::data::Envelope &&envelope){
  mu_od4.lock();

  opendlv::sim::scenario::Frame frame = cluon::extractMessage<opendlv::sim::scenario::Frame>(std::move(envelope));

  std::cout << "[FRAME][" << frame.scenario() << "][" << frame.run() << "][" << frame.frame() <<"]" << std::endl;
  std::ofstream out;
  std::string file = base_path_out + std::to_string(frame.scenario()) + "_" + std::to_string(frame.run()) + ".sres";
  if(frame.frame() == 0){
    out.open(file, std::ofstream::out | std::ofstream::trunc);
    out.close();
  }
  out.open(file, std::ios::app);
  if (out.is_open()){
    std::string str = (
      std::to_string(frame.frame()) + "," +
      std::to_string(frame.x()) + "," +
      std::to_string(frame.y()) + "," +
      std::to_string(frame.z()) + "," +
      std::to_string(frame.roll()) + "," +
      std::to_string(frame.pitch()) + "," +
      std::to_string(frame.yaw()) + "\n"
    );
    out << str;
  }else{
    std::cout << "[FRAME][FILE NOT OPEN]" << std::endl;

  }
  out.close();
  mu_od4.unlock();
};

int runScenario(const int s_id,const int r_id){

  mu_scenario.lock();
  opendlv::proxy::GroundSteeringRequest steer;
  opendlv::proxy::GroundAccelerationRequest acc;
  opendlv::proxy::GroundDeceleraionRequest dec;
  opendlv::sim::scenario::FrameRequest frameReq;
  opendlv::sim::scenario::Error error;

  steer.groundSteering(0.0);
  acc.groundAcceleration(0.0);
  dec.groundDeceleration(0.0);
  int frame = 0;

  std::ifstream file;
  file.open(base_path+std::to_string(s_id)+".path");

  std::cout << "[SCENARIO][" << s_id << "][" << s_id <<"][START]" << std::endl;
  if (file.is_open()){
    for(std::string line; std::getline(file, line); ){
      mu_od4.lock();
      if(scenarios.front().action() == 3){
        mu_od4.unlock();
        break;
      }
      mu_od4.unlock();

      frameReq.scenario(s_id);
      frameReq.run(r_id);
      frameReq.frame(frame);
      od4->send(frameReq);

      std::stringstream   linestream(line);
      std::string         value;
      int index = 0;

      while(std::getline(linestream,value,',')){
        float v = (float) std::stof (value);
        switch(index){
          case DELAY:{
              unsigned int d = (unsigned int) (v*1000000);
              usleep(d);
            }
            break;
          case STEERING:{
              steer.groundSteering(v);
              od4->send(steer);
            }
            break;
          case ACCELERATION:{
              if(v > 0){
                acc.groundAcceleration(v);
                od4->send(acc);
              }else{
                dec.groundDeceleration(v);
                od4->send(dec);
              }
            }
            break;
          case ERROR_ID:{
              error.errorId((int)v);
            }
            break;
          case ERROR_VALUE:{
              error.value(v);
              od4->send(error);
            }
            break;
        }
        index++;
      }
      frame++;
    }
    frameReq.scenario(s_id);
    frameReq.run(r_id);
    frameReq.frame(frame);
    od4->send(frameReq);
  }else{
    std::cout << "SCENARIO NOT FOUND" << std::endl;
  }


  opendlv::sim::scenario::Scenario scenario;
  scenario.scenario(s_id);
  scenario.run(r_id);
  scenario.action(3);
  od4->send(scenario);
  std::cout << "[SCENARIO][" << s_id << "][" << r_id <<"][END]" << std::endl;
  mu_scenario.unlock();
	return 0;
}

int main(int argc, char * argv[]) {
  uint16_t cid = 111;
  cluon::OD4Session tod4{cid};
  od4 = &tod4;
  od4->dataTrigger(opendlv::sim::scenario::Scenario::ID(), scenario_event);
  od4->dataTrigger(opendlv::sim::scenario::Frame::ID(), frame_event);

  mu_od4.lock();
  usleep(5000000);
  std::ifstream file;
  file.open(base_path+"scenarios");
  if (file.is_open()){
    for(std::string line; std::getline(file, line); ){
      std::stringstream   linestream(line);
      std::string         value;
      int index = 0;

      int scenario_id = 0;
      while(std::getline(linestream,value,',')){
        int v = (int) std::stoi (value);
        if(index == 0){
          scenario_id = v;
        }else{
          for (int i = 1; i <= v; i++) {
            opendlv::sim::scenario::Scenario scenario;
            scenario.scenario(scenario_id);
            scenario.run(i);
            scenario.track("bahrain");
            scenario.action(1);
            std::cout << "[SCENARIO][" << scenario.scenario() << "][" << scenario.run() << "][" << scenario.action()<<"][ADDING]" << std::endl;

            scenarios.push(scenario);
          }

        }
        index++;
      }

    }
  }
  if(scenarios.size() > 0){
    opendlv::sim::scenario::Scenario scenario = scenarios.front();
    std::cout << "[SCENARIO][" << scenario.scenario() << "][" << scenario.run() << "][" << scenario.action()<<"][BEGIN]" << std::endl;
    od4->send(scenario);
  }

  while(scenarios.size() > 0){

    mu_od4.unlock();
    usleep(3000000);
    mu_od4.lock();

  }
}*/
std::string base_path = "/test_cases/";
int main(int argc, char * argv[]) {
  usleep(5000000);
  std::ifstream file;
  file.open(base_path+"scenarios");
  std::vector<std::string> scenarios;
  if (file.is_open()){
    for(std::string line; std::getline(file, line); ){
      scenarios.push_back(line);
    }
  }
  for (int i = 0; i < scenarios.size(); i++) {
    std::stringstream   linestream(scenarios.at(i));
    std::string         value;
    int index = 0;

    int s_id;
    int runs;
    int test_cases;
    std::string algo;
    int cid = 111;
    while(std::getline(linestream,value,',')){
      switch (index) {
        case 0:
          s_id = (int) std::stoi (value);
        break;
        case 1:
          runs = (int) std::stoi (value);
        break;
        case 2:
          test_cases = (int) std::stoi (value);
        break;
        case 3:
          algo = value;
          break;
        case 4:
          cid = (int) std::stoi (value);
          break;
      }
      index++;
    }
    TestScenario test_scenario(s_id,runs,test_cases,algo,cid);
    test_scenario.run();
    while(!test_scenario.finished()){
      usleep(3000000);
    }
  }

}
