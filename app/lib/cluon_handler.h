#ifndef _CLUON_HANDLER_H
#define _CLUON_HANDLER_H

#include "cluon-complete.hpp"
#include "messages.hpp"

class CluonHandler{
  private:
    cluon::OD4Session * od4;
  public:
    CluonHandler();
    cluon::OD4Session* session();
    //void receive(cluon::data::Envelope &&envelope);
    void callbacks();
};

#endif
