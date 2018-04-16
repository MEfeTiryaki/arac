#include "arac_joystick/JoystickDummy.hpp"

namespace joystick {

template<typename KulmanModel_>
JoystickDummy<KulmanModel_>::JoystickDummy(kuco::AracModel& model)
    : JoystickHandlerBase<KulmanModel_>(model)
{
}


template<typename KulmanModel_>
JoystickDummy<KulmanModel_>::~JoystickDummy()
{
}

template<typename KulmanModel_>
void JoystickDummy<KulmanModel_>::advance()
{
  kuco::Velocity velocity = kuco::Velocity::Zero();
  kuco::AngularVelocity angularVelocity = kuco::AngularVelocity::Zero();

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
