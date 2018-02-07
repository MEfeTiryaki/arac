/*
 Author : M. Efe Tiryaki
 */

// param io
#include <param_io/get_param.hpp>

// arac gazebo
#include "arac_gazebo/KulmanGazeboPlugin.hpp"

namespace gazebo {

// Note : param_io is needed to use the getParam
using namespace param_io;

// Todo : check if we can add robot name here
KulmanGazeboPlugin::KulmanGazeboPlugin()
    : nodeHandle_(),
      isEstimatorUsed(false),
      jointNames_(4),
      jointPtrs_(4),
      jointTypes_(4),
      jointPositionsReset_(4),
      actuatorCommands_()
{
}

KulmanGazeboPlugin::~KulmanGazeboPlugin()
{
}

void KulmanGazeboPlugin::Init()
{
}
void KulmanGazeboPlugin::Reset()
{
}

void KulmanGazeboPlugin::Load(physics::ModelPtr model, sdf::ElementPtr sdf)
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

  // initialize joint structure
  initJointStructures();
  // initialize ROS pub/sub/services
  initPublishers();
  initSubscribers();

  //initServices();

  // reset simulation variables
  Reset();

  // connect to world updates from Gazebo
  this->updateConnection_ = event::Events::ConnectWorldUpdateBegin(
      boost::bind(&KulmanGazeboPlugin::OnUpdate, this));
}

void KulmanGazeboPlugin::OnUpdate()
{
  readSimulation();
  writeSimulation();
  publishTFs();
  publishPublishers();
}

void KulmanGazeboPlugin::readParameters(sdf::ElementPtr sdf)
{

  robotBaseLink_ = sdf->GetElement("robotBaseLink")->Get<std::string>();
  robotDescriptionParamName_ = sdf->GetElement("robotDescription")->Get<std::string>();
  const double statePublisherRate = sdf->GetElement("statePublisherRate")->Get<double>();

  publishingTimeStep_ = (statePublisherRate > 0.0) ? 1.0 / statePublisherRate : 0.0;

  getParam(*nodeHandle_, "frame/base/name", frameBase_);
  getParam(*nodeHandle_, "frame/odometry/name", frameOdometry_);
  getParam(*nodeHandle_, "frame/world/name", frameWorld_);

  getParam(*nodeHandle_, "joint_states/default_positions", jointPositionsDefault_);

  isEstimatorUsed = false;

}


// Note : RSL code for getting model of the robot
std::string KulmanGazeboPlugin::getUrdfRobotDescription(const std::string& paramName) const
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

void KulmanGazeboPlugin::initJointStructures()
{
  jointPtrs_ = model_->GetJoints();

  std::cout << "Detected Joints are :"<< std::endl;

  // Init the joint structures.
  for (int i = 0 ; i < jointPtrs_.size() ;i++) {
    const auto jointPtr = jointPtrs_[i];
    std::cout <<"  - " << jointPtr->GetName()<< std::endl;

    // Set joint position to default initial position
    jointPtr->SetPosition(0, jointPositionsDefault_[i]);
    jointPositionsReset_[i] = jointPositionsDefault_[i];
  }
}

void KulmanGazeboPlugin::initPublishers()
{

  // Robot State Publishers
  robotStatePublisher_ = nodeHandle_->advertise<arac_msgs::AracState>("/KulmanState",
                                                                      400);
  jointStatePublisher_ = nodeHandle_->advertise<sensor_msgs::JointState>("/KulmanState/joint_states",
                                                                        400);

  // Initilized the message
  kulmanStateMsg_ = arac_msgs::AracState();
  // kulmanStateMsg_.pose =
  // kulmanStateMsg_.twist =

  jointStates_ =  sensor_msgs::JointState();

  for (int i = 0 ; i < jointPtrs_.size() ;i++) {
    const auto jointPtr = jointPtrs_[i];
    jointStates_.name.push_back(jointPtr->GetName());
    jointStates_.position.push_back(0.0);
    jointStates_.velocity.push_back(0.0);
    jointStates_.effort.push_back(0.0);
  }
  kulmanStateMsg_.joints = jointStates_;


}

void KulmanGazeboPlugin::initSubscribers()
{

  // Actuator Command Subscriber
  const std::string subscriberStr = "/arac_controller_frame/ActuatorCommands";
  actuatorCommandSubscriber_ = nodeHandle_->subscribe(subscriberStr, 1,
                                                      &KulmanGazeboPlugin::actuatorCommandsCallback,
                                                      this);

  actuatorCommands_.inputs.name = jointNames_;
  actuatorCommands_.inputs.position = std::vector<double>(4, 0.0);
  actuatorCommands_.inputs.velocity = std::vector<double>(4, 0.0);
  actuatorCommands_.inputs.effort = std::vector<double>(4, 0.0);

}

// Todo : Actuator command is a kulman_msgs
void KulmanGazeboPlugin::actuatorCommandsCallback(const arac_msgs::ActuatorCommands& msg)
{
  //std::unique_lock < std::recursive_mutex > lock(gazeboMutex_);
  actuatorCommands_ = msg;
}


void KulmanGazeboPlugin::publishTFs()
{
  const auto& pose  = model_->GetLink(frameBase_)->GetWorldPose();
  // Odom
  odomTransform.setOrigin( tf::Vector3(pose.pos.x,pose.pos.y,pose.pos.z ));
  odomTransform.setRotation(tf::Quaternion(pose.rot.x,pose.rot.y,pose.rot.z,pose.rot.w));

  static tf::TransformBroadcaster br;
  br.sendTransform(tf::StampedTransform(odomTransform, ros::Time::now(), frameWorld_ , frameBase_));

}

void KulmanGazeboPlugin::publishPublishers()
{
    robotStatePublisher_.publish(kulmanStateMsg_);
    jointStatePublisher_.publish(jointStates_);
}

void KulmanGazeboPlugin::readSimulation(){
  jointStates_.header.stamp = ros::Time::now() ;
  kulmanStateMsg_.header.stamp = ros::Time::now() ;
  // read joint angles and write in publisher
  for (int i = 0 ; i < jointPtrs_.size() ;i++) {
    const auto jointPtr = jointPtrs_[i];
    jointStates_.position[i] = jointPtr->GetAngle(0).Radian();
    jointStates_.velocity[i] = jointPtr->GetVelocity(0);
    jointStates_.effort[i] = jointPtr->GetForce(0);
  }
  kulmanStateMsg_.joints = jointStates_;
}

}
