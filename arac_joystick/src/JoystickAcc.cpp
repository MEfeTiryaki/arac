#include "arac_joystick/JoystickAcc.hpp"

namespace joystick {

// Todo : check if we can add robot name here
JoystickAcc::JoystickAcc(kuco::AracModel& model)
    : JoystickHandlerBase(model),
      acceleration_(),
      accelerationMax_(kuco::Acceleration::Ones() * 5),
      accelerationFree_(kuco::Acceleration::Ones() * 0.005),
      angularAcceleration_(),
      angularAccelerationMax_(kuco::AngularAcceleration::Ones()),
      angularAccelerationFree_(kuco::AngularAcceleration::Ones() * 0.002),
      velocity_(),
      velocityMax_(kuco::Velocity::Ones() * 5),
      angularVelocity_(),
      angularVelocityMax_(kuco::AngularVelocity::Ones()),
      inputSamplingTime_(0.1),
      jerk_(0.1),
      angularJerk_(0.1),
      didUserInputRecieved_(false)
{
}

JoystickAcc::~JoystickAcc()
{
}

void JoystickAcc::advance()
{
  const double jerk = 10;
  const double angularJerk = 10;
  const double jerkFree = 1;
  const double angularJerkFree = 1;

  double dt = inputSamplingTime_;

  if (didUserInputRecieved_) {

    if (joystickMsg_.linear.x > 0) {
      jerk_ = jerk;
    } else if (joystickMsg_.linear.x < 0) {
      jerk_ = -jerk;
    } else {
      jerk_ = 0.0;
    }

    if (joystickMsg_.angular.z > 0) {
      angularJerk_ = angularJerk;
    } else if (joystickMsg_.angular.z < 0) {
      angularJerk_ = -angularJerk;
    } else {
      angularJerk_ = 0.0;
    }


    // Reset the Velocity Commands Back to 0
    joystickMsg_.linear.x = 0.0;
    joystickMsg_.angular.z = 0.0;

    // Acceleration Update II

    if ((acceleration_[0] + jerk_ * dt < accelerationMax_[0]) && (acceleration_[0] + jerk_ * dt > -accelerationMax_[0])) {
      acceleration_[0] += jerk_ * dt;
    } else if(acceleration_[0] + jerk_ * dt >= accelerationMax_[0]){
      acceleration_[0] = accelerationMax_[0];
    } else{
      acceleration_[0] = -accelerationMax_[0];
    }
    // Angular Acceleration Update

    if ((angularAcceleration_[0] + angularJerk_ * dt < angularAccelerationMax_[0]) && (angularAcceleration_[0] + angularJerk_ * dt > -angularAccelerationMax_[0])) {
      angularAcceleration_[0] += angularJerk_ * dt;
    } else if(angularAcceleration_[0] + angularJerk_ * dt >= angularAccelerationMax_[0]){
      angularAcceleration_[0] = angularAccelerationMax_[0];
    } else{
      angularAcceleration_[0] = -angularAccelerationMax_[0];
    }

    didUserInputRecieved_ = false;

  } else if (!didUserInputRecieved_ ) {
    // && ros::Time::now().toSec() - joystickCommandStartTime_ >= inputSamplingTime_
    jerk_= jerkFree ;
    angularJerk_ = angularJerkFree ;
    if (velocity_[0] > 0) {
      //acceleration_[0] = -accelerationFree_[0];
      acceleration_[0] -= jerk_ * dt;
    } else if (velocity_[0] < 0) {
      //acceleration_[0] = accelerationFree_[0];
      acceleration_[0] += jerk_ * dt;
    } else {
      acceleration_[0] = 0.0;
    }

    if (angularVelocity_[0] > 0) {
//      angularAcceleration_[0] = -angularAccelerationFree_[0];
      angularAcceleration_[0] -= angularJerk_ * dt;
    } else if (angularVelocity_[0] < 0) {
//      angularAcceleration_[0] = angularAccelerationFree_[0];
      angularAcceleration_[0] += angularJerk_ * dt;
    } else {
      angularAcceleration_[0] = 0.0;
    }
  }

  // Velocity Update
  if (jerk_ != 0) {
    if ((velocity_[0] + acceleration_[0] * dt < velocityMax_[0]) && (velocity_[0] + acceleration_[0] * dt > -velocityMax_[0])) {
      velocity_[0] += acceleration_[0] * dt;
    } else if(velocity_[0] + acceleration_[0] * dt >= velocityMax_[0]){
      velocity_[0] = velocityMax_[0];
    } else{
      velocity_[0] = -velocityMax_[0];
    }

  } else {
    if ((velocity_[0] + acceleration_[0] * dt) * velocity_[0] > 0.0) {
      velocity_[0] = acceleration_[0] * dt;
    } else {
      velocity_[0] = 0.0;
    }
  }

  if (angularJerk_ != 0) {
    if ((angularVelocity_[0] + angularAcceleration_[0] * dt < angularVelocityMax_[0]) && (angularVelocity_[0] + angularAcceleration_[0] * dt > -angularVelocityMax_[0])) {
      angularVelocity_[0] += angularAcceleration_[0] * dt;
    } else if(angularVelocity_[0] + angularAcceleration_[0] * dt >= angularVelocityMax_[0]){
      angularVelocity_[0] = angularVelocityMax_[0];
    } else{
      angularVelocity_[0] = -angularVelocityMax_[0];
    }

  }else {
    if ((angularVelocity_[0] + angularAcceleration_[0] * dt) * angularVelocity_[0] > 0.0) {
      angularVelocity_[0] = angularAcceleration_[0] * dt;
    } else {
      angularVelocity_[0] = 0.0;
    }
  }

  //*
  std::cout << "__________________________________________________________________________"
            << std::endl;
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
  if (ros::Time::now().toSec() - joystickCommandStartTime_ >= inputSamplingTime_) {
    joystickMsg_ = msg;
    joystickCommandStartTime_ = ros::Time::now().toSec();
    didUserInputRecieved_ = true;
  }
}

}

