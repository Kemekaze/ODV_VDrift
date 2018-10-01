#ifndef _TERROR_H
#define _TERROR_H

#include <algorithm>
#include "messages.hpp"
#include "cluon-complete.hpp"
#include "test_scenario.h"


class TestError{
  private:
    int _test_case;
    int _type;
    int _type2;
    int _position;
    int _position2;
    float _value;
    float _value2;
    float _deviation;

    TestScenario * scenario;

    std::uniform_real_distribution<float> mutation;
    float mutation_rate = 0.25;
  public:
    TestError(TestScenario *scenario, int test_case, int type, int type2, int position, int position2, float value, float value2):
    _test_case(test_case),
    _type(type),
    _type2(type2),
    _position(position),
    _position2(position2),
    _value(value),
    _value2(value2),
    mutation(0.0, 1.0){
      this->scenario = scenario;
    }

    TestError& operator=(TestError other){
       scenario = other.scenario;
       _test_case = other._test_case;
       _type = other._type;
       _type2 = other._type2;
       _position = other._position;
       _position2 = other._position2;
       _value = other._value;
       _value2 = other._value2;
       mutation = other.mutation;
       return *this;
   }

    void sendError(int action);
    TestError crossover(TestError other);
    void mutate();
    void deviation(float v);
    float deviation();

    int type();
    int position();
    float value();

    int type2();
    int position2();
    float value2();




};

#endif
