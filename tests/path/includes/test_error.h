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
    int _position;
    float _value;
    float _deviation;

    TestScenario * scenario;

    std::uniform_real_distribution<float> mutation;
    float mutation_rate = 0.25;
  public:
    TestError(TestScenario *scenario, int test_case, int type,int position, float value):
    _test_case(test_case),
    _type(type),
    _position(position),
    _value(value),
    mutation(0.0, 1.0){
      this->scenario = scenario;
    }

    TestError& operator=(TestError other){
       scenario = other.scenario;
       _test_case = other._test_case;
       _type = other._type;
       _position = other._position;
       _value = other._value;
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




};

#endif
