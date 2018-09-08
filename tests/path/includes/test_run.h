#include "test_scenario.h"
#ifndef _TEST_RUN_H
#define _TEST_RUN_H
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
#include <mutex>
#include <queue>


#include "update_car.h"
#include "messages.hpp"
#include "cluon-complete.hpp"


using std::string;
//class TestScenario;

class TestRun{
  private:


    //TestResult result;
    int run_id;
    int current_action = 0;
    std::vector<UpdateCar> actions;

    TestScenario * scenario;
  public:
    std::vector<opendlv::sim::scenario::Frame> frames;
    TestRun(int run_id, TestScenario * scenario): run_id(run_id){
      this->scenario = scenario;
    }
    void start();
    void end();
    void run();
    void initialize(string path);
    void addAction(string line);
    void addFrame(opendlv::sim::scenario::Frame frame);

    static const int START = 1;
    static const int END = 3;




};

#endif
