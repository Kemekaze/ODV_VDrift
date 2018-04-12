#include "cluon_handler.h"
CluonHandler::CluonHandler(){
  //std::function<void(cluon::data::Envelope&&)> cb = std:bind(&CluonHandler::receive, &this)
  cluon::OD4Session od4(111,[this](cluon::data::Envelope &&envelope) noexcept {
    this->receive(std::move(envelope));
  });
  this->od4 = &od4;
}

cluon::OD4Session* CluonHandler::session() {
  return this->od4;
}

void CluonHandler::receive(cluon::data::Envelope &&envelope) {
  if (envelope.dataType() == opendlv::sim::Frame::ID()) {
      opendlv::sim::Frame frame = cluon::extractMessage<opendlv::sim::Frame>(std::move(envelope));
      std::cout << "Sent a message Frame.x " << frame.x() << "." << std::endl;
  }
}
