/*
 name : State.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/

#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include <vector>

#pragma once

namespace kuco {
  // Todo (Efe Tiryaki 16.02.18): Bu arkadaşlaro typedef headerı içinde başka bir yerde tanımla
  // daha genel kullanıma açılsın
//  typedef std::vector<double>  Position ;
//  typedef std::vector<double>  Quaternion ;
//  typedef std::vector<double>  Velocity ;
//  typedef std::vector<double>  AngularVelocity ;
//  typedef std::vector<double>  Acceleration ;
//  typedef std::vector<double>  AngularAcceleration ;
//  typedef std::vector<double>  Force ;
//  typedef std::vector<double>  Torque ;

  class State {
  public:
    State();

    virtual ~State();

    std::vector<double>  getPositionInWorldFrame();
    void setPositionInWorldFrame(std::vector<double>  pos);

    std::vector<double>  getOrientationInWorldFrame();
    void setOrientationInWorldFrame(std::vector<double>  q);

    Eigen::Matrix<double, 3, 1>   getVelocityInWorldFrame();
    void setVelocityInWorldFrame(Eigen::Matrix<double, 3, 1>  vel);

    std::vector<double>  getAngularVelocityInWorldFrame();
    void setAngularVelocityInWorldFrame(std::vector<double>  angVel);

    std::vector<double>  getAccelerationInWorldFrame();
    void setAccelerationInWorldFrame(std::vector<double>  acc);

    std::vector<double>  getAngularAccelerationInWorldFrame();
    void setAngularAccelerationInWorldFrame(std::vector<double>  angAcc);

    std::vector<double>  getForceInWorldFrame();
    void setForceInWorldFrame(std::vector<double>  f);

    std::vector<double>   getTorqueInWorldFrame();
    void setTorqueInWorldFrame(std::vector<double>  t);

    std::vector<double>  getVelocityInBaseFrame();
    void setVelocityInBaseFrame(std::vector<double>  vel);

    std::vector<double>  getAngularVelocityInBaseFrame();
    void setAngularVelocityIBaseFrame(std::vector<double>  angVel);

    std::vector<double>  getAccelerationInBaseFrame();
    void setAccelerationInBaseFrame(std::vector<double>  acc);

    std::vector<double>  getAngularAccelerationInBaseFrame();
    void setAngularAccelerationInBaserame(std::vector<double>  angAcc);

    std::vector<double>  getForceInBaseFrame();
    void setForceInBaseFrame(std::vector<double>  f);

    std::vector<double>  getTorqueInBaseFrame();
    void setTorqueInBaserame(std::vector<double>  t);

   private:

     std::vector<double>  positionInWorldFrame_ ;
     std::vector<double>  orientationInWorldFrame_ ;
     Eigen::Matrix<double, 3, 1>  velocityInWorldFrame_ ;
     std::vector<double>  angularVelocityInWorldFrame_ ;
     std::vector<double>  accelerationInWorldFrame_ ;
     std::vector<double>  angularAccelerationInWorldFrame_ ;
     std::vector<double>  forceInWorldFrame_ ;
     std::vector<double>  torqueInWorldFrame_ ;

     std::vector<double>  velocityInBaseFrame_ ;
     std::vector<double>  angularVelocityInBaseFrame_ ;
     std::vector<double>  accelerationInBaseFrame_ ;
     std::vector<double>  angularAccelerationInBaseFrame_ ;
     std::vector<double>  forceInBaseFrame_ ;
     std::vector<double>  torqueInBaseFrame_ ;

  };

}/* namespace kuco*/
