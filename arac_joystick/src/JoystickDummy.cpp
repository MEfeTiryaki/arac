
#include "arac_joystick/JoystickDummy.hpp"

namespace joystick{

// Todo : check if we can add robot name here
JoystickDummy::JoystickDummy(kuco::State& state):
    JoystickHandlerBase(state)
{
}

JoystickDummy::~JoystickDummy()
{
}

void JoystickDummy::advance()
{
  if (ros::Time::now().toSec()-joystickCommandStartTime_>0.5){
    state_.setLinearVelocityInX(0.0) ;
    state_.setAngularVelocityInZ(0.0) ;

  }else{
    state_.setLinearVelocityInX(joystickMsg_.linear.x) ;
    state_.setAngularVelocityInZ(joystickMsg_.angular.z) ;
  }

}

}
