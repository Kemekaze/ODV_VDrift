#include "cluon_handler.h"

template <typename T>
void CluonHandler::send(T &message){
  od4.send(message);
}

bool CluonHandler::isRunning(){
  return od4.isRunning();
}



void CluonHandler::callbacks(){
  od4.dataTrigger(opendlv::sim::KinematicState::ID(), [this](cluon::data::Envelope &&envelope){
    mu.lock();
    opendlv::sim::KinematicState ks = cluon::extractMessage<opendlv::sim::KinematicState>(std::move(envelope));
    std::cout << "[VDRIFT]["<< cid <<"][R][" << ks.vx() <<"][" << ks.vy() <<"][" << ks.yawRate() << "]" << std::endl;
    this->kinematicState = std::move(ks);
    mu.unlock();
  });
}
opendlv::sim::KinematicState CluonHandler::getKinematicState(){
    mu.lock();
    opendlv::sim::KinematicState ks = kinematicState;
    mu.unlock();
    return ks;
}
