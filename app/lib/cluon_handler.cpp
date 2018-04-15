#include "cluon_handler.h"
CluonHandler::CluonHandler(){
  cluon::OD4Session od4(111,[](cluon::data::Envelope &&envelope) {
    if (envelope.dataType() == opendlv::sim::Frame::ID()) {
        opendlv::sim::Frame frame = cluon::extractMessage<opendlv::sim::Frame>(std::move(envelope));
        std::cout << "Sent a message Frame.x " << frame.x() << "." << std::endl;
    }
  });
  //cluon::OD4Session od4{111};
  this->od4 = &od4;
  this->callbacks();
}

cluon::OD4Session* CluonHandler::session() {
  return this->od4;
}

/*void CluonHandler::receive(cluon::data::Envelope &&envelope) {
  if (envelope.dataType() == opendlv::sim::Frame::ID()) {
      opendlv::sim::Frame frame = cluon::extractMessage<opendlv::sim::Frame>(std::move(envelope));
      std::cout << "Sent a message Frame.x " << frame.x() << "." << std::endl;
  }
}*/
void CluonHandler::callbacks(){
  //CANT FIND DATATRIGGER
  /*this->od4->dataTrigger(opendlv::sim::Frame::ID(), [](cluon::data::Envelope &&envelope){
    opendlv::sim::Frame frame = cluon::extractMessage<opendlv::sim::Frame>(std::move(envelope));
    std::cout << "Sent a message Frame.x " << frame.x() << "." << std::endl;
  });*/
}
