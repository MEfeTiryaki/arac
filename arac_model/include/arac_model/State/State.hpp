/*
 name : State.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/


#pragma once

namespace kuco {
  typedef Eigen::Vector3d Position ;
  typedef Eigen::Vector4d Quaternion ;
  typedef Eigen::Vector3d Velocity ;
  typedef Eigen::Vector3d AngularVelocity ;
  typedef Eigen::Vector3d Acceleration ;
  typedef Eigen::Vector3d AngularAcceleration ;
  typedef Eigen::Vector3d Force ;
  typedef Eigen::Vector3d Torque ;

  class State {
  public:
    State();

    virtual ~State();

    double getLinearVelocityInX(){ return linearVelocityInX_ ;};
    void   setLinearVelocityInX(double vel){ linearVelocityInX_ = vel ;};

    double getAngularVelocityInZ(){ return angularVelocityInZ_ ;};
    void   setAngularVelocityInZ(double vel){ angularVelocityInZ_ = vel ;};

   private:
     double linearVelocityInX_;
     double angularVelocityInZ_;

     Position positionInWorldFrame_ ;
     Quaternion orientationInWorldFrame_ ;
     Velocity velocityInWorldFrame_ ;
     AngularVelocity angularVelocityInWorldFrame_ ;
     Acceleration accelerationInWorldFrame_ ;
     AngularAcceleration angularAccelerationInWorldFrame_ ;
     Force forceInWorldFrame_ ;
     Torque forqueInWorldFrame_ ;

     Velocity velocityInBaseFrame_ ;
     AngularVelocity angularVelocityInBaseFrame_ ;
     Acceleration accelerationInBaseFrame_ ;
     AngularAcceleration angularAccelerationInBaseFrame_ ;
     Force forceInBaseFrame_ ;
     Torque forqueInBaseFrame_ ;

  };

}/* namespace kuco*/
