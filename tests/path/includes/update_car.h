#ifndef _ACTTION_H
#define _ACTTION_H

#include "test_scenario.h"
#include "messages.hpp"
#include "cluon-complete.hpp"


using std::string;
class TestScenario;
class UpdateCar{
  private:
    static const int DELAY = 0;
    static const int STEERING = 1;
    static const int ACCELERATION = 2;
    unsigned int _delay;
    opendlv::proxy::GroundSteeringRequest steer;
    opendlv::proxy::GroundAccelerationRequest acc;

  public:
    UpdateCar(std::string line);
    void run(TestScenario* s);


};

#endif
