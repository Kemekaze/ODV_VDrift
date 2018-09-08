#include "test_scenario.h"

UpdateCar::UpdateCar(std::string line){
  std::stringstream   linestream(line);
  std::string         value;
  int index = 0;

  while(std::getline(linestream,value,',')){
    float v = (float) std::stof (value);
    switch(index){
      case UpdateCar::DELAY:{
          _delay = (unsigned int) (v*1000000);
        }
        break;
      case UpdateCar::STEERING:{
          steer.groundSteering(v);
        }
        break;
      case UpdateCar::ACCELERATION:{
          acc.groundAcceleration(v);
        }
        break;
    }
    index++;
  }
}

void UpdateCar::run(TestScenario* s){
  usleep(_delay);
  s->send(steer);
  s->send(acc);
}
