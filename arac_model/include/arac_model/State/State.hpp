/*
 name : State.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#include <Eigen/Core>

// Kindr library for physical variables
#include <kindr/Core>
#include <iostream>
#include <vector>

#pragma once

namespace kuco {
// Todo (Efe Tiryaki 16.02.18): Bu arkadaşlaro typedef headerı içinde başka bir yerde tanımla
// daha genel kullanıma açılsın
typedef std::vector<double> Position;
typedef std::vector<double> Quaternion;
typedef kindr::Velocity3D Velocity;
typedef std::vector<double> AngularVelocity;
typedef std::vector<double> Acceleration;
typedef std::vector<double> AngularAcceleration;
typedef std::vector<double> Force;
typedef std::vector<double> Torque;

class State
{
 public:
  State();

  virtual ~State();

  const kindr::Position3D& getPositionInWorldFrame() const;

  void setPositionInWorldFrame(const kindr::Position3D& pos);

  //
  const kindr::QuaternionD& getOrientationInWorldFrame() const;

  void setOrientationInWorldFrame(const kindr::QuaternionD& q);

  //
  const kindr::Velocity3D& getVelocityInWorldFrame() const;

  void setVelocityInWorldFrame(const kindr::Velocity3D& vel);

  //
  const kindr::AngularVelocity3D& getAngularVelocityInWorldFrame() const;

  void setAngularVelocityInWorldFrame(const kindr::AngularVelocity3D& angVel);

  //
  const kindr::Acceleration3D& getAccelerationInWorldFrame() const ;
  void setAccelerationInWorldFrame(const kindr::Acceleration3D& acc);

  const kindr::AngularAcceleration3D& getAngularAccelerationInWorldFrame()const;
  void setAngularAccelerationInWorldFrame( const kindr::AngularAcceleration3D& angAcc);

  const kindr::Force3D& getForceInWorldFrame()const;
  void setForceInWorldFrame(const kindr::Force3D& f);

  const kindr::Torque3D& getTorqueInWorldFrame()const;
  void setTorqueInWorldFrame(const kindr::Torque3D& t);

 protected:

  kindr::Position3D positionInWorldFrame_;
  kindr::QuaternionD orientationInWorldFrame_;
  kindr::Velocity3D velocityInWorldFrame_;
  kindr::AngularVelocity3D angularVelocityInWorldFrame_;
  kindr::Acceleration3D accelerationInWorldFrame_;
  kindr::AngularAcceleration3D angularAccelerationInWorldFrame_;
  kindr::Force3D forceInWorldFrame_;
  kindr::Torque3D torqueInWorldFrame_;

};

}/* namespace kuco*/
