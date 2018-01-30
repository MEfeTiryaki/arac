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


void AracGazeboPlugin::readSimulation()
{

}

void AracGazeboPlugin::writeSimulation()
{

  for (int i = 0 ;i<4 ;i++ ) {
    double jointVelocity = actuatorCommands_.inputs.velocity[i];
    jointPtrs_[i]->SetVelocity(0, jointVelocity);
  }

}

// Todo : Check if this can be made through configs and yaml
void AracGazeboPlugin::initJointStructures()
{

  // Todo : Make this more generic
  jointNames_[0]="LF_WH";
  jointNames_[1]="RF_WH";
  jointNames_[2]="LH_WH";
  jointNames_[3]="RH_WH";

  int i = 0;
  for (const auto jointName : jointNames_) {
    jointNametoJointId_.insert(std::make_pair(jointName, i++));
  }


   i = 0;
// Init the joint structures.
  for (const auto jointName : jointNames_) {

    auto joint = robotDescriptionUrdfModel_.getJoint(jointName);

    if (!joint) {
      std::cout << "gazebo_ros_control : " << "Joint named '" << jointName
                << "' does not exist in the URDF model." << std::endl;
      return;
    }

    auto jointPtr = this->model_->GetJoint(jointName);

    if (!jointPtr) {
      std::cout << "gazebo_ros_control : " << "Joint named '" << jointName
                << "' does not exist in Gazebo." << std::endl;
      return;
    }

    jointPtrs_[i] = jointPtr;

    // Set joint position to default initial position
    jointPtrs_[i]->SetPosition(0, jointPositionsDefault_[i]);

    jointTypes_[i]=joint->type;
    jointPositionsReset_[i] = jointPositionsDefault_[i];

    i++;
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
