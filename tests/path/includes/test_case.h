#ifndef _TCASE_H
#define _TCASE_H

#include "messages.hpp"
#include "cluon-complete.hpp"


using std::string;

class TestCase{
  private:

    int postition;
    int value;
    int error;
  public:
    TestCase(int id,int value);
    void run(TestScenario* s);


};

#endif
