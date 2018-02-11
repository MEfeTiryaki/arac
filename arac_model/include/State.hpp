
/*
 * joystickHandlerBase.cpp
 *
 *  Created on: Feb 11 , 2018
 *      Author: efe
 */
 #pragma once



namespace kuco {
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


  };

}/* namespace kuco*/
