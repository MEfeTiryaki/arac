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
  Eigen::Matrix<double, 3, 1> velocity = Eigen::Matrix<double, 3, 1>::Zero();
  Eigen::Vector3d angularVelocity = Eigen::Vector3d::Zero();

  if (ros::Time::now().toSec() - joystickCommandStartTime_ > 0.5) {
    //velocity = {0.0,0.0,0.0};
    //angularVelocity = {0.0,0.0,0.0};
  } else {
    velocity[0] = joystickMsg_.linear.x;
    angularVelocity[2] = joystickMsg_.angular.z;
  }

  model_.getGovde().getDesiredState().setVelocityInWorldFrame(velocity);
  //model_.getGovde().getDesiredState().setAngularVelocityInWorldFrame(angularVelocity);

}

}
