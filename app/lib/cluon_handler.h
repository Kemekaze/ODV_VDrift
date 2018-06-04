#ifndef _CLUON_HANDLER_H
#define _CLUON_HANDLER_H


#include <mutex>
#include "cluon-complete.hpp"
#include "messages.hpp"


class CluonHandler{
  private:
    uint16_t cid;
    cluon::OD4Session od4;

    std::mutex mu;
    opendlv::sim::KinematicState kinematicState;
  public:
    CluonHandler(uint16_t CID) : cid(CID), od4{CID} { this->callbacks();};

    void callbacks();
    template <typename T>
    void send(T &message);
    bool isRunning();
    opendlv::sim::KinematicState getKinematicState();

};

#endif
