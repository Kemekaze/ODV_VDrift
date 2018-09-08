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
    this->kinematicState = std::move(ks);
    mu.unlock();
  });

  od4.dataTrigger(opendlv::sim::scenario::FrameRequest::ID(), [this](cluon::data::Envelope &&envelope){
    mu.lock();
    opendlv::sim::scenario::FrameRequest fr = cluon::extractMessage<opendlv::sim::scenario::FrameRequest>(std::move(envelope));
    opendlv::sim::scenario::Frame sc_frame;
    sc_frame.scenario(fr.scenario());
    sc_frame.run(fr.run());
    sc_frame.frame(fr.frame());
    sc_frame.x(frame.x());
    sc_frame.y(frame.y());
    sc_frame.z(frame.z());
    sc_frame.roll(frame.roll());
    sc_frame.pitch(frame.pitch());
    sc_frame.yaw(frame.yaw());
    send(sc_frame);
    mu.unlock();
  });

  /*od4.dataTrigger(opendlv::sim::scenario::Scenario::ID(), [this](cluon::data::Envelope &&envelope){
    mu.lock();
    std::cout << "[VDRIFT][SCENARIO??]" << std::endl;
    mu.unlock();
  });*/

}

opendlv::sim::KinematicState CluonHandler::getKinematicState(){
    mu.lock();
    opendlv::sim::KinematicState ks = kinematicState;
    mu.unlock();
    return ks;
}
void CluonHandler::updateKinematicState(float vx, float vy, float vz, float rollRate, float pitchRate, float yawRate){
    mu.lock();

    mu.unlock();
}
void CluonHandler::updateFrame(float x, float y, float z, float roll, float pitch, float yaw){
    mu.lock();
    frame.x(x);
    frame.y(y);
    frame.z(z);
    frame.roll(roll);
    frame.pitch(pitch);
    frame.yaw(yaw);
    mu.unlock();
}
