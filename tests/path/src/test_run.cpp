#include "test_run.h"


void TestRun::start(){
  opendlv::sim::scenario::Scenario s;
  s.scenario(scenario->getScenario());
  s.run(run_id);
  s.track("bahrain");
  s.action(TestRun::START);
  scenario->send(s);
}
void TestRun::end(){
  opendlv::sim::scenario::Scenario s;
  s.scenario(scenario->getScenario());
  s.run(run_id);
  s.action(TestRun::END);
  scenario->send(s);
}
void TestRun::run(){
  while(current_action < actions.size()){
    actions.at(current_action).run(scenario);
    //std::cout << "TESTCASE[" << run_id << "]ACTION[" << current_action << "][" << std::to_string(scenario->hasTestCase()) << "]" << std::endl;
    opendlv::sim::scenario::FrameRequest frameReq;
    frameReq.scenario(scenario->getScenario());
    frameReq.run(run_id);
    frameReq.frame(current_action);
    scenario->send(frameReq);
    scenario->insertError(current_action);
    /*if(scenario->hasTestCase()){
       if(scenario->hasSteeringError(current_action)){
         opendlv::sim::scenario::Error error;
         error.errorId(1);
         error.value(scenario->steeringError());
       }
       if(scenario->hasFrictionError(current_action)){
         opendlv::sim::scenario::Error error;
         error.errorId(1);
         error.value(scenario->frictionError());
         scenario->send(error);
         std::thread ([this](){
           usleep(3000000);
           opendlv::sim::scenario::Error error;
           error.errorId(1);
           error.value(1.0);
           scenario->send(error);
         }).detach();
       }
    }*/

    ++current_action;
  }
  end();
}

void TestRun::addAction(std::string line){
  UpdateCar uc = UpdateCar(line);
  actions.push_back(uc);
}
void TestRun::addFrame(opendlv::sim::scenario::Frame frame){
  frames.push_back(frame);
}
