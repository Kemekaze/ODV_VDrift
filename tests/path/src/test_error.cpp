#include "test_error.h"

void TestError::sendError(int action){
  int t = 0;
  float v = 0;
  if(action == _position){
    t = _type;
    v =_value;
  }else if(action == _position2){
    t = _type2;
    v = _value2;
  }else {
    return;
  }
  opendlv::sim::scenario::Error error;
  error.errorId(t);
  error.value(v);
  scenario->send(error);
  if(_type == 1){
    std::thread ([this](){
      usleep(3000000);
      opendlv::sim::scenario::Error error;
      error.errorId(1);
      error.value(1.0);
      scenario->send(error);
    }).detach();
  }
}


TestError TestError::crossover(TestError other){
  bool type_diff = _type != other._type;
  if((scenario->error_gen(scenario->mt) % 2) == 0){
     if(type_diff){
        _type = other._type;
        _type2 = other._type2;
      }
      _value = other._value;
      _value2 = other._value2;
  }else{
    _position = other._position;
    _position2 = other._position2;
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
      _position2 = scenario->error_gen(scenario->mt);
      break;
    case 1:
      _type = scenario->error_gen(scenario->mt) % 2 + 1;
      if(_type == 1) _type2 = 2;
      if(_type == 1){
        _value = scenario->friction_error_gen(scenario->mt);
        _value2 = scenario->steering_error_gen(scenario->mt);
      }else if(_type == 2){
        _value = scenario->steering_error_gen(scenario->mt);
        _value2 = scenario->friction_error_gen(scenario->mt);
      }
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

int TestError::type2(){
  return _type2;
}
int TestError::position2(){
  return _position2;
}
float TestError::value2(){
  return _value2;
}
