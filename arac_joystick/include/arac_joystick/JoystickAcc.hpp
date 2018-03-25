/*
 * joystickHandlerBase.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: efe
 */

#include "arac_joystick/JoystickHandlerBase.hpp"

 namespace joystick {
class JoystickAcc : public JoystickHandlerBase{
public:
  JoystickAcc(kuco::AracModel& model);

  virtual ~JoystickAcc();

  virtual void advance() override;

protected:

  virtual void getJoystickMsg(geometry_msgs::Twist msg);

 private:

 kuco::Acceleration acceleration_;
 kuco::Acceleration accelerationFree_;

 kuco::AngularAcceleration angularAcceleration_;
 kuco::AngularAcceleration angularAccelerationFree_;

 kuco::Velocity velocity_;
 kuco::Velocity velocityMax_;

 kuco::AngularVelocity angularVelocity_;
 kuco::AngularVelocity angularVelocityMax_;

 double inputSamplingTime_;
};

}
