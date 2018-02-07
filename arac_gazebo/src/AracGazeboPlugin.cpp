/*
 Author : M. Efe Tiryaki
 */

// param io
#include <param_io/get_param.hpp>

// arac gazebo
#include "arac_gazebo/AracGazeboPlugin.hpp"

namespace gazebo {

// Note : param_io is needed to use the getParam
using namespace param_io;
AracGazeboPlugin::AracGazeboPlugin()
    : KulmanGazeboPlugin()
{
}

AracGazeboPlugin::~AracGazeboPlugin()
{

}



void AracGazeboPlugin::writeSimulation()
{

  for (int i = 0 ;i<4 ;i++ ) {
    double jointVelocity = actuatorCommands_.inputs.velocity[i];
    jointPtrs_[i]->SetVelocity(0, jointVelocity);
  }

}

void AracGazeboPlugin::initPublishers()
{
  KulmanGazeboPlugin::initPublishers();

  if (isEstimatorUsed) {
    // Todo : implement Imu data for state estimation
    imuDataPublisher_ = nodeHandle_->advertise<sensor_msgs::Imu>(robotName_ + "/ImuData", 1);
    // Todo : implement joint data for state estimation
    actuatorDataPublisher_ = nodeHandle_->advertise<sensor_msgs::JointState>(
        robotName_ + "/ActuatorData", 1);
  }
}

void AracGazeboPlugin::initSubscribers()
{
  KulmanGazeboPlugin::initSubscribers();
}


GZ_REGISTER_MODEL_PLUGIN(AracGazeboPlugin)
}
