
#include "arac_joystick/JoystickDummy.hpp"

namespace joystick{

// Todo : check if we can add robot name here
JoystickDummy::JoystickDummy():
    JoystickHandlerBase()
{
}

JoystickDummy::~JoystickDummy()
{
}

void JoystickDummy::advance()
{
  if (ros::Time::now().toSec()-joystickCommandStartTime_>0.5){
    linVelocity_ = 0.0 ;
    angVelocity_ = 0.0 ;

  }else{
    linVelocity_ = joystickMsg_.linear.x;
    linVelocity_ = joystickMsg_.angular.z;
  }
}

}
