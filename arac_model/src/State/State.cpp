/*
 name : State.cpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/

#include "arac_model/State/State.hpp"

namespace kuco{

// Todo : check if we can add robot name here
State::State()
  : positionInWorldFrame_(),
    orientationInWorldFrame_(),
    velocityInWorldFrame_(),
    angularVelocityInWorldFrame_(),
    accelerationInWorldFrame_(),
    angularAccelerationInWorldFrame_(),
    forceInWorldFrame_(),
    torqueInWorldFrame_(),

    velocityInBaseFrame_(),
    angularVelocityInBaseFrame_(),
    accelerationInBaseFrame_(),
    angularAccelerationInBaseFrame_(),
    forceInBaseFrame_(),
    torqueInBaseFrame_()
{
  linearVelocityInX_ = 0.0 ;
  angularVelocityInZ_= 0.0 ;
}

State::~State()
{
}

Position State::getPositionInWorldFrame(){
  return positionInWorldFrame_;
}
void State::setPositionInWorldFrame(Position pos){
  positionInWorldFrame_ = pos ;
}

Quaternion State::getOrientationInWorldFrame(){
  return orientationInWorldFrame_ ;
}
void State::setOrientationInWorldFrame(Quaternion q){
  orientationInWorldFrame_ = q ;
}

Velocity State::getVelocityInWorldFrame(){
  return velocityInWorldFrame_ ;
}
void State::setVelocityInWorldFrame(Velocity vel){
  velocityInWorldFrame_ = vel ;
}

AngularVelocity State::getAngularVelocityInWorldFrame(){
  return angularVelocityInWorldFrame_ ;
}
void State::setAngularVelocityInWorldFrame(AngularVelocity angVel){
  angularVelocityInWorldFrame_ = angVel ;
}

Acceleration State::getAccelerationInWorldFrame(){
  return accelerationInWorldFrame_ ;
}
void State::setAccelerationInWorldFrame(Acceleration acc){
  accelerationInWorldFrame_ = acc ;
}

AngularAcceleration State::getAngularAccelerationInWorldFrame(){
  return angularAccelerationInWorldFrame_ ;
}
void State::setAngularAccelerationInWorldFrame(AngularAcceleration angAcc){
  angularAccelerationInWorldFrame_ = angAcc ;
}

Force State::getForceInWorldFrame(){
  return forceInWorldFrame_ ;
}
void State::setForceInWorldFrame(Force f){
  forceInWorldFrame_ = f ;
}

Torque State::getTorqueInWorldFrame(){
  return torqueInWorldFrame_ ;
}
void State::setTorqueInWorldFrame(Torque t){
  torqueInWorldFrame_ = t ;
}

Velocity State::getVelocityInBaseFrame(){
  return velocityInBaseFrame_ ;
}
void State::setVelocityInBaseFrame(Velocity vel)
  velocityInBaseFrame_ = vel ;
}

AngularVelocity State::getAngularVelocityInBaseFrame(){
  return angularVelocityInBaseFrame_ ;
}
void State::setAngularVelocityIBaseFrame(AngularVelocity angVel){
  angularVelocityInBaseFrame_ = angVel ;
}

Acceleration State::getAccelerationInBaseFrame(){
  return accelerationInBaseFrame_;
}
void State::setAccelerationInBaseFrame(Acceleration acc){
  accelerationInBaseFrame_ = acc ;
}

AngularAcceleration State::getAngularAccelerationInBaseFrame(){
  return angularAccelerationInBaseFrame_ ;
}
void State::setAngularAccelerationInBaserame(AngularAcceleration angAcc){
  angularAccelerationInBaseFrame_ = angAcc ;
}

Force State::getForceInBaseFrame(){
  return forceInBaseFrame_ ;
}
void State::setForceInBaseFrame(Force f){
  forceInBaseFrame_ = f ;
}

Torque State::getTorqueInBaseFrame(){
  return torqueInBaseFrame_ ;
}
void State::setTorqueInBaserame(Torque t){
  torqueInBaseFrame_ = t ;
}



}/* namespace kuco*/
