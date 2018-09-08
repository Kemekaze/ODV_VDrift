#include "test_error.h"

void TestError::sendError(int action){
  if(action != _position) return;
  opendlv::sim::scenario::Error error;
  error.errorId(_type);
  error.value(_value);
  scenario->send(error);
  if(_type == 1){
    std::thread ([this](){
      usleep(3000000);
      opendlv::sim::scenario::Error error;
      error.errorId(_type);
      error.value(1.0);
      scenario->send(error);
    }).detach();
  }
}


TestError TestError::crossover(TestError other){
  bool type_diff = _type != other._type;
  if((scenario->error_gen(scenario->mt) % 2) == 0){
     if(type_diff) _type = other._type;
      _value = other._value;
  }else{
    _position = other._position;
  }
  /*if((scenario->error_gen(scenario->mt) % 2) == 0) _position = other._position;
  if((scenario->error_gen(scenario->mt) % 2) == 0){
    if(type_diff) _type = other._type;
    _value = other._value;
  }*/
}
void TestError::mutate(){
  if(mutation(scenario->mt) > mutation_rate) return;

  int m = scenario->error_gen(scenario->mt) % 2;
  switch (m) {
    case 0:
      _position = scenario->error_gen(scenario->mt);
      break;
    case 1:
      _type = scenario->error_gen(scenario->mt) % 2 + 1;
      if(_type == 1)
        _value = scenario->friction_error_gen(scenario->mt);
      else if(_type == 2)
        _value = scenario->steering_error_gen(scenario->mt);
      break;
  }
}

void TestError::deviation(float v){
  _deviation = v;
}

float TestError::deviation(){
  return _deviation;
}


int TestError::type(){
  return _type;
}
int TestError::position(){
  return _position;
}
float TestError::value(){
  return _value;
}
