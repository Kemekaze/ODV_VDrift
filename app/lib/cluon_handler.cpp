#include "cluon_handler.h"

template <typename T>
void CluonHandler::send(T &message){
  this->od4.send(message);
}

bool CluonHandler::isRunning(){
  return this->od4.isRunning();
}

std::vector <float> CluonHandler::getControlInputs(){
  std::vector<float> inputs(CarInput::INVALID, 0.0f);
  this->mu.lock();
  inputs[CarInput::THROTTLE] = this->acc.groundAcceleration();
  inputs[CarInput::BRAKE] = this->dec.groundDeceleration();
  if(this->steer.groundSteering() > 0.0f){
    inputs[CarInput::STEER_RIGHT] = 1.0f;
    inputs[CarInput::STEER_LEFT] = 0.0f;
  }else if(this->steer.groundSteering() < 0.0f){
    inputs[CarInput::STEER_LEFT] = 1.0f;
    inputs[CarInput::STEER_RIGHT] = 0.0f;
  }else{
    inputs[CarInput::STEER_RIGHT] = 0.0f;
    inputs[CarInput::STEER_LEFT] = 0.0f;
  }
  this->mu.unlock();
  return inputs;
}

void CluonHandler::callbacks(){
  this->od4.dataTrigger(opendlv::proxy::GroundSteeringRequest::ID(), [this](cluon::data::Envelope &&envelope){
    this->mu.lock();
    std::cout << "Recieved " << envelope.dataType()<< std::endl;
    opendlv::proxy::GroundSteeringRequest r = cluon::extractMessage<opendlv::proxy::GroundSteeringRequest>(std::move(envelope));
    this->steer = std::move(r);
    this->mu.unlock();
  });
  this->od4.dataTrigger(opendlv::proxy::GroundAccelerationRequest::ID(), [this](cluon::data::Envelope &&envelope){
    this->mu.lock();
    std::cout << "Recieved " << envelope.dataType()<< std::endl;
    opendlv::proxy::GroundAccelerationRequest r = cluon::extractMessage<opendlv::proxy::GroundAccelerationRequest>(std::move(envelope));
    this->acc = std::move(r);
    this->mu.unlock();
  });
  this->od4.dataTrigger(opendlv::proxy::GroundDecelerationRequest::ID(), [this](cluon::data::Envelope &&envelope){
    this->mu.lock();
    std::cout << "Recieved " << envelope.dataType()<< std::endl;
    opendlv::proxy::GroundDecelerationRequest r = cluon::extractMessage<opendlv::proxy::GroundDecelerationRequest>(std::move(envelope));
    this->dec = std::move(r);
    this->mu.unlock();
  });
}
