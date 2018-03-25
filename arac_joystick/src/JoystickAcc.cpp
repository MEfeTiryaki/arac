#include "arac_joystick/JoystickAcc.hpp"

namespace joystick {

// Todo : check if we can add robot name here
JoystickAcc::JoystickAcc(kuco::AracModel& model)
    : JoystickHandlerBase(model),
      acceleration_(),
      accelerationFree_(kuco::Acceleration::Ones() * 0.005),
      angularAcceleration_(),
      angularAccelerationFree_(kuco::AngularAcceleration::Ones() * 0.002),
      velocity_(),
      velocityMax_(kuco::Velocity::Ones() * 10),
      angularVelocity_(),
      angularVelocityMax_(kuco::AngularVelocity::Ones() * 5),
      inputSamplingTime_(0.01)
{
}

JoystickAcc::~JoystickAcc()
{
}

void JoystickAcc::advance()
{
  const double acc = 10;
  const double angularAcc = 10;
  const double accFree = 3;
  const double angularAccFree = 3;

  bool isAccFree = false;
  bool isAngularAccFree = false;
  double dt = inputSamplingTime_;

  // Todo : change the name of the  joystickCommandStartTime_
  if (ros::Time::now().toSec() - joystickCommandStartTime_ >= inputSamplingTime_) {
    if (joystickMsg_.linear.x > 0) {
      acceleration_[0] = acc;
    } else if (joystickMsg_.linear.x < 0) {
      acceleration_[0] = -acc;
    } else {
      isAccFree = true;
      if (velocity_[0] > 0) {
        acceleration_[0] = -accFree;
      } else if (velocity_[0] < 0) {
        acceleration_[0] = accFree;
      } else {
        acceleration_[0] = 0.0;
      }
    }
    if (joystickMsg_.angular.z > 0) {
      angularAcceleration_[2] = angularAcc;
    } else if (joystickMsg_.angular.z < 0) {
      angularAcceleration_[2] = -angularAcc;
    } else {
      isAngularAccFree = true;
      if (angularVelocity_[2] > 0) {
        angularAcceleration_[2] = -angularAccFree;
      } else if (angularVelocity_[2] < 0) {
        angularAcceleration_[2] = angularAccFree;
      } else {
        angularAcceleration_[2] = 0.0;
      }
    }
    // Reset the Velocity Commands Back to 0
    joystickMsg_.linear.x = 0.0;
    joystickMsg_.angular.z = 0.0;

    if (!isAccFree) {
      if ((velocity_[0] + acceleration_[0] * dt < velocityMax_[0])
          && (velocity_[0] + acceleration_[0] * dt > -velocityMax_[0])) {
        velocity_[0] += acceleration_[0] * dt;
      } else if (velocity_[0] + acceleration_[0] * dt >= velocityMax_[0]) {
        velocity_[0] = velocityMax_[0];
      } else {
        velocity_[0] = -velocityMax_[0];
      }
    } else {

      if ((velocity_[0] + acceleration_[0] * dt) * velocity_[0] > 0.0) {
        if ((velocity_[0] + acceleration_[0] * dt < velocityMax_[0])
            && (velocity_[0] + acceleration_[0] * dt > -velocityMax_[0])) {
          velocity_[0] += acceleration_[0] * dt;
        } else if (velocity_[0] + acceleration_[0] * dt >= velocityMax_[0]) {
          velocity_[0] = velocityMax_[0];
        } else {
          velocity_[0] = -velocityMax_[0];
        }
      } else {
        velocity_[0] = 0.0;
      }
      isAccFree = false;
    }
    if (!isAngularAccFree) {
      if ((angularVelocity_[2] + angularAcceleration_[2] * dt < angularVelocityMax_[2])
          && (angularVelocity_[2] + angularAcceleration_[2] * dt > -angularVelocityMax_[2])) {
        angularVelocity_[2] += angularAcceleration_[2] * dt;
      } else if (angularVelocity_[0] + angularAcceleration_[2] * dt >= angularVelocityMax_[2]) {
        angularVelocity_[2] = angularVelocityMax_[2];
      } else {
        angularVelocity_[2] = -angularVelocityMax_[2];
      }
    } else {
      if ((angularVelocity_[2] + angularAcceleration_[2] * dt) * angularVelocity_[2] > 0.0) {
        if ((angularVelocity_[2] + angularAcceleration_[2] * dt < angularVelocityMax_[2])
            && (angularVelocity_[2] + angularAcceleration_[2] * dt > -angularVelocityMax_[2])) {
          angularVelocity_[2] += angularAcceleration_[2] * dt;
        } else if (angularVelocity_[2] + angularAcceleration_[2] * dt >= angularVelocityMax_[2]) {
          angularVelocity_[2] = angularVelocityMax_[2];
        } else {
          angularVelocity_[2] = -angularVelocityMax_[2];
        }
      } else {
        angularVelocity_[2] = 0.0;
      }
      isAngularAccFree = false;
    }

    joystickCommandStartTime_ = ros::Time::now().toSec();
  }
  // ELSE DO NOTHING

  std::cout << "__________________________________________________________________________"
      << std::endl;
  std::cout << "time : " << ros::Time::now().toSec() << std::endl;
  std::cout << "acceleration : " << acceleration_.transpose() << std::endl;
  std::cout << "angularAcceleration : " << angularAcceleration_.transpose() << std::endl;
  std::cout << "velocity : " << velocity_.transpose() << std::endl;
  std::cout << "angularVelociy : " << angularVelocity_.transpose() << std::endl;
  //*/

  model_.getGovde().getDesiredState().setVelocityInWorldFrame(velocity_);
  model_.getGovde().getDesiredState().setAngularVelocityInWorldFrame(angularVelocity_);

}

void JoystickAcc::getJoystickMsg(geometry_msgs::Twist msg)
{
  joystickMsg_ = msg;
  //joystickCommandStartTime_ = ros::Time::now().toSec();
}

}
