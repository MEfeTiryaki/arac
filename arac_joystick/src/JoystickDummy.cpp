#include "arac_joystick/JoystickDummy.hpp"

namespace joystick {

// Todo : check if we can add robot name here
JoystickDummy::JoystickDummy(kuco::AracModel& model)
    : JoystickHandlerBase(model)
{
}

JoystickDummy::~JoystickDummy()
{
}

void JoystickDummy::advance()
{
  kindr::Velocity3D velocity = kindr::Velocity3D::Zero();
  kindr::AngularVelocity3D angularVelocity = kindr::AngularVelocity3D::Zero();

  if (ros::Time::now().toSec() - joystickCommandStartTime_ > 0.5) {
    //velocity = {0.0,0.0,0.0};
    //angularVelocity = {0.0,0.0,0.0};
  } else {
    velocity << joystickMsg_.linear.x, 0.0 , 0.0 ;
    angularVelocity << 0.0 , 0.0 , joystickMsg_.angular.z;
  }

  model_.getGovde().getDesiredState().setVelocityInWorldFrame(velocity);
  model_.getGovde().getDesiredState().setAngularVelocityInWorldFrame(angularVelocity);

}

}
