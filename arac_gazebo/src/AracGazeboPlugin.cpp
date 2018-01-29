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
    : nodeHandle_(),
      isEstimatorUsed(false),
      jointNames_(4),
      jointPtrs_(4),
      jointTypes_(4),
      jointPositionsReset_(4),
      actuatorCommands_()
{
}

AracGazeboPlugin::~AracGazeboPlugin()
{
}

void AracGazeboPlugin::Init()
{
}

void AracGazeboPlugin::Reset()
{
}

void AracGazeboPlugin::Load(physics::ModelPtr model, sdf::ElementPtr sdf)
{
  // To ensure that gazebo is not distrubed while loading
  //std::unique_lock<std::recursive_mutex> lock(gazeboMutex_);

  // XXX : "~" getParam'da başa gelen salak cift // den kurtarıyor
  nodeHandle_ = new ros::NodeHandle("~");

  // Note : check if this is placed correctly
  this->readParameters(sdf);

  // Model
  this->model_ = model;

  // request the robot_description parameter
  robotDescriptionUrdfString_ = getUrdfRobotDescription(robotDescriptionParamName_);

  // parse the URDF string into a URDF model structure
  robotDescriptionUrdfModel_.initString(robotDescriptionUrdfString_);

  initJointStructures();
  // initialize ROS pub/sub/services
  initPublishers();
  initSubscribers();

  //initServices();

  // reset simulation variables
  Reset();

  // connect to world updates from Gazebo
  this->updateConnection_ = event::Events::ConnectWorldUpdateBegin(
      boost::bind(&AracGazeboPlugin::OnUpdate, this));
}

void AracGazeboPlugin::OnUpdate()
{
  writeSimulation();
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

void AracGazeboPlugin::readParameters(sdf::ElementPtr sdf)
{

  robotBaseLink_ = sdf->GetElement("robotBaseLink")->Get<std::string>();
  robotDescriptionParamName_ = sdf->GetElement("robotDescription")->Get<std::string>();
  const double statePublisherRate = sdf->GetElement("statePublisherRate")->Get<double>();
  publishingTimeStep_ = (statePublisherRate > 0.0) ? 1.0 / statePublisherRate : 0.0;

  getParam(*nodeHandle_, "frame/base/name", frameBase_);
  getParam(*nodeHandle_, "frame/odometry/name", frameOdometry_);
  getParam(*nodeHandle_, "frame/world/name", frameWorld_);
  getParam(*nodeHandle_, "frame/world_gravity_aligned/name", frameWorldGravityAligned_);

  getParam(*nodeHandle_, "joint_states/default_positions", jointPositionsDefault_);

  isEstimatorUsed = false;
}

// Note : RSL code for getting model of the robot
std::string AracGazeboPlugin::getUrdfRobotDescription(const std::string& paramName) const
{
  std::cout << "[" << robotName_
            << "GazeboPlugin::getUrdfRobotDescription] Loading urdf description." << std::endl;

  std::string urdfString;
  const double timeOut = 5.0;  // [s]
  auto start = std::chrono::steady_clock::now();
  while (urdfString.empty()) {
    std::string searchParamName;
    if (nodeHandle_->searchParam(paramName, searchParamName)) {
      std::cout << "[" << robotName_
                << "GazeboPlugin::getUrdfRobotDescription] Waiting for model URDF in parameter "
                << searchParamName << " on the ROS parameter server." << std::endl;
      nodeHandle_->getParam(searchParamName, urdfString);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    auto now = std::chrono::steady_clock::now();

    if ((std::chrono::duration_cast < std::chrono::seconds > (now - start)).count() >= timeOut) {
      std::cout << "[" << robotName_
                << "GazeboPlugin::getUrdfRobotDescription] Timeout while loading urdf!"
                << std::endl;

      break;
    }
  }
  std::cout << "[" << robotName_
            << "GazeboPlugin::getUrdfRobotDescription] Received urdf from parameter server."
            << std::endl;

  return urdfString;
}


// Todo : Bok gibi oldu düzelt!!
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

    auto jointPtr = model_->GetJoint(jointName);

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

  // Robot State Publishers
  robotStatePublisher_ = nodeHandle_->advertise<arac_msgs::AracState>(robotName_ + "/RobotState",
                                                                      1);

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

// Actuator Command Subscriber
  const std::string subscriberStr = "/arac_controller_frame/ActuatorCommands";
  actuatorCommandSubscriber_ = nodeHandle_->subscribe(subscriberStr, 1,
                                                      &AracGazeboPlugin::setActuatorCommands, this);

  actuatorCommands_.inputs.name = jointNames_;
  actuatorCommands_.inputs.position = std::vector<double>(4,0.0);
  actuatorCommands_.inputs.velocity = std::vector<double>(4,0.0);
  actuatorCommands_.inputs.effort = std::vector<double>(4,0.0);

}

// Todo : name callbacks as callback
void AracGazeboPlugin::setActuatorCommands(const arac_msgs::ActuatorCommands& msg)
{
  //std::unique_lock < std::recursive_mutex > lock(gazeboMutex_);
  actuatorCommands_ = msg;
}

GZ_REGISTER_MODEL_PLUGIN(AracGazeboPlugin)
}
