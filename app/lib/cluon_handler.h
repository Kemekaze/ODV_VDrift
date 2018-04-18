#ifndef _CLUON_HANDLER_H
#define _CLUON_HANDLER_H


#include <mutex>
#include "cluon-complete.hpp"
#include "messages.hpp"
#include "_vdrift/physics/carinput.h"


class CluonHandler{
  private:
    cluon::OD4Session od4;

    std::mutex mu;
    opendlv::proxy::GroundSteeringRequest steer;
    opendlv::proxy::GroundAccelerationRequest acc;
    opendlv::proxy::GroundDecelerationRequest dec;
  public:
    CluonHandler(uint16_t CID) : od4{CID} { this->callbacks();};
    //cluon::OD4Session session();
    void callbacks();
    template <typename T>
    void send(T &message);
    bool isRunning();
    std::vector <float> getControlInputs();
};

#endif
