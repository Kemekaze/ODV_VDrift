#ifndef _TEST_SCENARIO_H
#define _TEST_SCENARIO_H


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
#include <random>
#include <algorithm>

#include "test_run.h"
#include "update_car.h"
#include "messages.hpp"
#include "cluon-complete.hpp"
#include "test_error.h"
#include "dtw.h"


class TestError;

class TestScenario{
  private:
    /*static final double ga_uniformRate    = 0.5;
    static final double ga_mutationRate   = 0.015;
    static final int    ga_tournamentSize = 5;
    static final bool   ga_elitism        = true;*/




    std::string base_path = "/test_cases/";

    int cid;
    int scenario_id;
    std::string test_method;
    cluon::OD4Session od4;
    std::mutex mu_od4;
    std::vector<TestRun> runs;
    int current_run = 0;
    int current_test_case = 0;
    int total_runs;
    int test_cases;
    int total_actions_run = 1;
    bool is_base_run = true;

    //not the best way to store them;
    int *errors;
    float *steering_errors;
    float *friction_errors;
    float *error_results;

    std::vector<TestError> run_errors;

    TestRun base_run;

    void scenarioEvent(opendlv::sim::scenario::Scenario scenario);
    void frameEvent(opendlv::sim::scenario::Frame frame);

    std::function<void(cluon::data::Envelope &&envelope)> scenario_event = [this](cluon::data::Envelope &&envelope){
      mu_od4.lock();
      opendlv::sim::scenario::Scenario scenario = cluon::extractMessage<opendlv::sim::scenario::Scenario>(std::move(envelope));
      scenarioEvent(std::move(scenario));
      mu_od4.unlock();
    };
    std::function<void(cluon::data::Envelope &&envelope)> frame_event = [this](cluon::data::Envelope &&envelope){
      mu_od4.lock();
      opendlv::sim::scenario::Frame frame = cluon::extractMessage<opendlv::sim::scenario::Frame>(std::move(envelope));
      frameEvent(std::move(frame));
      mu_od4.unlock();
    };




    void initialize(int runs);

  public:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> error_gen;
    std::uniform_real_distribution<float> friction_error_gen;
    std::uniform_real_distribution<float> steering_error_gen;


    TestScenario(int scenario_id, int runs, int test_cases, std::string test_method, int cid):
      scenario_id(scenario_id),
      test_method(test_method),
      test_cases(test_cases),
      total_runs(runs),
      cid(cid),
      od4{cid},
      base_run(0,this),
      mt(rd()),
      steering_error_gen(-0.1,0.1),
      friction_error_gen(0.3,1.0)
      {
        initialize(runs);
      }
    template <typename T>
    void send(T &message){
      this->od4.send(message);
    }
    double run();

    bool finished(){
      return current_run == total_runs;
    }
    int getScenario(){
      return scenario_id;
    }
    int mc();
    int ga();

    void generateErrors();
    float getDeviation();

    TestError generateRandomFitest(int fittest);

    void insertError(int action);


    bool hasTestCase();
    /*
    bool hasSteeringError(int test_case);
    float steeringError();
    bool hasFrictionError(int test_case);
    float frictionError();*/


};

#endif
