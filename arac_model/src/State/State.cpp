/*
 name : State.cpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#include "arac_model/State/State.hpp"

namespace kuco {

State::State()
    : positionInWorldFrame_(3),
      orientationInWorldFrame_(4),
      velocityInWorldFrame_(3),
      angularVelocityInWorldFrame_(3),
      accelerationInWorldFrame_(3),
      angularAccelerationInWorldFrame_(3),
      forceInWorldFrame_(3),
      torqueInWorldFrame_(3),
      velocityInBaseFrame_(3),
      angularVelocityInBaseFrame_(3),
      accelerationInBaseFrame_(3),
      angularAccelerationInBaseFrame_(3),
      forceInBaseFrame_(3),
      torqueInBaseFrame_(3)
{
}

State::~State()
{
}

std::vector<double> State::getPositionInWorldFrame()
{
  return positionInWorldFrame_;
}
void State::setPositionInWorldFrame(std::vector<double> pos)
{
  positionInWorldFrame_ = pos;
}

std::vector<double> State::getOrientationInWorldFrame()
{
  return orientationInWorldFrame_;
}
void State::setOrientationInWorldFrame(std::vector<double> q)
{
  orientationInWorldFrame_ = q;
}

Eigen::Matrix<double, 3, 1> State::getVelocityInWorldFrame()
{
  return velocityInWorldFrame_;
}
void State::setVelocityInWorldFrame(Eigen::Matrix<double, 3, 1> vel)
{
  velocityInWorldFrame_= (Eigen::Matrix<double, 3, 1>)vel;
}

std::vector<double> State::getAngularVelocityInWorldFrame()
{
  return angularVelocityInWorldFrame_;
}
void State::setAngularVelocityInWorldFrame(std::vector<double> angVel)
{
  angularVelocityInWorldFrame_ = angVel;
}

std::vector<double> State::getAccelerationInWorldFrame()
{
  return accelerationInWorldFrame_;
}
void State::setAccelerationInWorldFrame(std::vector<double> acc)
{
  accelerationInWorldFrame_ = acc;
}

std::vector<double> State::getAngularAccelerationInWorldFrame()
{
  return angularAccelerationInWorldFrame_;
}
void State::setAngularAccelerationInWorldFrame(std::vector<double> angAcc)
{
  angularAccelerationInWorldFrame_ = angAcc;
}

std::vector<double> State::getForceInWorldFrame()
{
  return forceInWorldFrame_;
}
void State::setForceInWorldFrame(std::vector<double> f)
{
  forceInWorldFrame_ = f;
}

std::vector<double> State::getTorqueInWorldFrame()
{
  return torqueInWorldFrame_;
}
void State::setTorqueInWorldFrame(std::vector<double> t)
{
  torqueInWorldFrame_ = t;
}

std::vector<double> State::getVelocityInBaseFrame()
{
  return velocityInBaseFrame_;
}
void State::setVelocityInBaseFrame(std::vector<double> vel)
{
  velocityInBaseFrame_ = vel;
}

std::vector<double> State::getAngularVelocityInBaseFrame()
{
  return angularVelocityInBaseFrame_;
}
void State::setAngularVelocityIBaseFrame(std::vector<double> angVel)
{
  angularVelocityInBaseFrame_ = angVel;
}

std::vector<double> State::getAccelerationInBaseFrame()
{
  return accelerationInBaseFrame_;
}
void State::setAccelerationInBaseFrame(std::vector<double> acc)
{
  accelerationInBaseFrame_ = acc;
}

std::vector<double> State::getAngularAccelerationInBaseFrame()
{
  return angularAccelerationInBaseFrame_;
}
void State::setAngularAccelerationInBaserame(std::vector<double> angAcc)
{
  angularAccelerationInBaseFrame_ = angAcc;
}

std::vector<double> State::getForceInBaseFrame()
{
  return forceInBaseFrame_;
}
void State::setForceInBaseFrame(std::vector<double> f)
{
  forceInBaseFrame_ = f;
}

std::vector<double> State::getTorqueInBaseFrame()
{
  return torqueInBaseFrame_;
}
void State::setTorqueInBaserame(std::vector<double> t)
{
  torqueInBaseFrame_ = t;
}

}
;
/* namespace kuco*/
