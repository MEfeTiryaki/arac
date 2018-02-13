/*
 name : State.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/

#include <Eigen/Core>

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

    Position getPositionInWorldFrame();
    void setPositionInWorldFrame(Position pos);

    Quaternion getOrientationInWorldFrame();
    void setOrientationInWorldFrame(Quaternion q);

    Velocity getVelocityInWorldFrame();
    void setVelocityInWorldFrame(Velocity vel);

    AngularVelocity getAngularVelocityInWorldFrame();
    void setAngularVelocityInWorldFrame(AngularVelocity angVel);

    Acceleration getAccelerationInWorldFrame();
    void setAccelerationInWorldFrame(Acceleration acc);

    AngularAcceleration getAngularAccelerationInWorldFrame();
    void setAngularAccelerationInWorldFrame(AngularAcceleration angAcc);

    Force getForceInWorldFrame();
    void setForceInWorldFrame(Force f);

    Torque getTorqueInWorldFrame();
    void setTorqueInWorldFrame(Torque t);

    Velocity getVelocityInBaseFrame();
    void setVelocityInBaseFrame(Velocity vel);

    AngularVelocity getAngularVelocityInBaseFrame();
    void setAngularVelocityIBaseFrame(AngularVelocity angVel);

    Acceleration getAccelerationInBaseFrame();
    void setAccelerationInBaseFrame(Acceleration acc);

    AngularAcceleration getAngularAccelerationInBaseFrame();
    void setAngularAccelerationInBaserame(AngularAcceleration angAcc);

    Force getForceInBaseFrame();
    void setForceInBaseFrame(Force f);

    Torque getTorqueInBaseFrame();
    void setTorqueInBaserame(Torque t);

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
     Torque torqueInWorldFrame_ ;

     Velocity velocityInBaseFrame_ ;
     AngularVelocity angularVelocityInBaseFrame_ ;
     Acceleration accelerationInBaseFrame_ ;
     AngularAcceleration angularAccelerationInBaseFrame_ ;
     Force forceInBaseFrame_ ;
     Torque torqueInBaseFrame_ ;

  };

}/* namespace kuco*/
