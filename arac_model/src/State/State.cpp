/*
 name : State.cpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#include "arac_model/State/State.hpp"

namespace kuco {

State::State()
    : positionInWorldFrame_(),
      orientationInWorldFrame_(),
      velocityInWorldFrame_(),
      angularVelocityInWorldFrame_(),
      accelerationInWorldFrame_(),
      angularAccelerationInWorldFrame_(),
      forceInWorldFrame_(),
      torqueInWorldFrame_()
{
}

State::~State()
{
}

//
const kindr::Position3D&  State::getPositionInWorldFrame() const
{
  return positionInWorldFrame_;
}

void State::setPositionInWorldFrame( const kindr::Position3D& pos)
{
  positionInWorldFrame_ = pos;
}

//
const kindr::QuaternionD& State::getOrientationInWorldFrame() const
{
  return orientationInWorldFrame_;
}

void State::setOrientationInWorldFrame(const kindr::QuaternionD& q)
{
  orientationInWorldFrame_ = q;
}

//
const kindr::Velocity3D& State::getVelocityInWorldFrame() const
{
  return velocityInWorldFrame_;
}

void State::setVelocityInWorldFrame(const kindr::Velocity3D& vel)
{
  velocityInWorldFrame_= vel;
}

//
const kindr::AngularVelocity3D& State::getAngularVelocityInWorldFrame() const
{
  return angularVelocityInWorldFrame_;
}

void State::setAngularVelocityInWorldFrame(const kindr::AngularVelocity3D& angVel)
{
  angularVelocityInWorldFrame_ = angVel;
}

//
const kindr::Acceleration3D& State::getAccelerationInWorldFrame() const
{
  return accelerationInWorldFrame_;
}
void State::setAccelerationInWorldFrame(const kindr::Acceleration3D&  acc)
{
  accelerationInWorldFrame_ = acc;
}

const kindr::AngularAcceleration3D&  State::getAngularAccelerationInWorldFrame() const
{
  return angularAccelerationInWorldFrame_;
}
void State::setAngularAccelerationInWorldFrame(const kindr::AngularAcceleration3D&  angAcc)
{
  angularAccelerationInWorldFrame_ = angAcc;
}

const kindr::Force3D& State::getForceInWorldFrame() const
{
  return forceInWorldFrame_;
}
void State::setForceInWorldFrame(const kindr::Force3D&  f)
{
  forceInWorldFrame_ = f;
}

const kindr::Torque3D&  State::getTorqueInWorldFrame() const
{
  return torqueInWorldFrame_;
}
void State::setTorqueInWorldFrame(const kindr::Torque3D& t)
{
  torqueInWorldFrame_ = t;
}

//std::vector<double> State::getVelocityInBaseFrame()
//{
//  return velocityInBaseFrame_;
//}
//void State::setVelocityInBaseFrame(std::vector<double> vel)
//{
//  velocityInBaseFrame_ = vel;
//}
//
//std::vector<double> State::getAngularVelocityInBaseFrame()
//{
//  return angularVelocityInBaseFrame_;
//}
//void State::setAngularVelocityIBaseFrame(std::vector<double> angVel)
//{
//  angularVelocityInBaseFrame_ = angVel;
//}
//
//std::vector<double> State::getAccelerationInBaseFrame()
//{
//  return accelerationInBaseFrame_;
//}
//void State::setAccelerationInBaseFrame(std::vector<double> acc)
//{
//  accelerationInBaseFrame_ = acc;
//}
//
//std::vector<double> State::getAngularAccelerationInBaseFrame()
//{
//  return angularAccelerationInBaseFrame_;
//}
//void State::setAngularAccelerationInBaserame(std::vector<double> angAcc)
//{
//  angularAccelerationInBaseFrame_ = angAcc;
//}
//
//std::vector<double> State::getForceInBaseFrame()
//{
//  return forceInBaseFrame_;
//}
//void State::setForceInBaseFrame(std::vector<double> f)
//{
//  forceInBaseFrame_ = f;
//}
//
//std::vector<double> State::getTorqueInBaseFrame()
//{
//  return torqueInBaseFrame_;
//}
//void State::setTorqueInBaserame(std::vector<double> t)
//{
//  torqueInBaseFrame_ = t;
//}

}
;
/* namespace kuco*/
