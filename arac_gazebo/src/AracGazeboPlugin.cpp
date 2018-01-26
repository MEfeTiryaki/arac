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
  AracGazeboPlugin::AracGazeboPlugin(){}

  AracGazeboPlugin::~AracGazeboPlugin(){}

  void AracGazeboPlugin::Load(physics::ModelPtr model, sdf::ElementPtr sdf)
  {
    // To ensure that gazebo is not distrubed while loading
    std::unique_lock<std::recursive_mutex> lock(gazeboMutex_);
    nodeHandle_ = new ros::NodeHandle("~");

    // Note : check if this is placed correctly
    readParameters(sdf);

    // Model
    model_ = model ;

    // request the robot_description parameter
    robotDescriptionUrdfString_ = getUrdfRobotDescription(robotDescriptionParamName_);

    // parse the URDF string into a URDF model structure
    robotDescriptionUrdfModel_.initString(robotDescriptionUrdfString_);

    // initialize ROS pub/sub/services
    initPublishers();
    initSubscribers();
    initServices();

    // reset simulation variables
    Reset();

    // connect to world updates from Gazebo
    updateConnection_ = event::Events::ConnectWorldUpdateBegin(
          boost::bind(&AracGazeboPlugin::OnUpdate, this));
  }

  void AracGazeboPlugin::readParameters( sdf::ElementPtr sdf )
  {
    robotName_  = sdf->GetElement("robotName")->Get<std::string>();
    robotBaseLink_ = sdf->GetElement("robotBaseLink")->Get<std::string>();
    robotDescriptionParamName_ = sdf->GetElement("robotDescription")->Get<std::string>();
    const double statePublisherRate = sdf->GetElement("statePublisherRate")->Get<double>();
    publishingTimeStep_ = (statePublisherRate > 0.0) ? 1.0 / statePublisherRate : 0.0;

    getParam(*nodeHandle_, "frame/base/name", frameBase_);
    getParam(*nodeHandle_, "frame/odometry/name", frameOdometry_);
    getParam(*nodeHandle_, "frame/world/name", frameWorld_);
    getParam(*nodeHandle_, "frame/world_gravity_aligned/name", frameWorldGravityAligned_);

    getParam(*nodeHandle_, "joint_states/default_positions", jointPositionsDefault_);

  }


  // Note : RSL code for getting model of the robot
  std::string AracGazeboPlugin::getUrdfRobotDescription(const std::string& paramName) const {
    std::cout <<"[" << robotName_ << "GazeboPlugin::getUrdfRobotDescription] Loading urdf description."<<std::endl;

    std::string urdfString;
    const double timeOut = 5.0; // [s]
    auto start = std::chrono::steady_clock::now();
    while (urdfString.empty()) {
      std::string searchParamName;
      if (nodeHandle_->searchParam(paramName, searchParamName)) {
        std::cout <<"[" << robotName_ << "GazeboPlugin::getUrdfRobotDescription] Waiting for model URDF in parameter " << searchParamName << " on the ROS parameter server."<<std::endl;
        nodeHandle_->getParam(searchParamName, urdfString);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      auto now = std::chrono::steady_clock::now();

      if ((std::chrono::duration_cast<std::chrono::seconds>(now - start)).count() >= timeOut) {
        std::cout <<"[" << robotName_ << "GazeboPlugin::getUrdfRobotDescription] Timeout while loading urdf!"<<std::endl;

        break;
      }
    }
    std::cout <<"[" << robotName_ << "GazeboPlugin::getUrdfRobotDescription] Received urdf from parameter server."<<std::endl;

    return urdfString;
  }

  void AracGazeboPlugin::initJointStructures(){
    // Todo : Make this more generic
    jointNames_.push_back("LF_WH");
    jointNames_.push_back("RF_WH");
    jointNames_.push_back("LH_WH");
    jointNames_.push_back("RH_WH");

    int i = 0 ;
    for (const auto jointName: jointNames_){
      jointNametoJointId_.insert(std::make_pair(jointName,i++));
    }

    // Init the joint structures.
    for (const auto jointName : jointNames_ ) {

      auto joint = robotDescriptionUrdfModel_.getJoint(jointName);
      if (!joint) {
        std::cout<<"gazebo_ros_control : "<< "Joint named '" << jointName << "' does not exist in the URDF model."<<std::endl;
        return;
      }

      auto jointPtr =  model_->GetJoint(jointName);

      if (!jointPtr) {
        std::cout<<"gazebo_ros_control : "<<  "Joint named '" << jointName << "' does not exist in Gazebo."<<std::endl;
        return;
      }

      jointPtrs_.push_back(jointPtr);

      // Set joint position to default initial position
      jointPtrs_.back()->SetPosition(0, jointPositionsDefault_[jointNametoJointId_[jointName]]);

      jointTypes_.push_back(joint->type) ;
      jointPositionsReset_.push_back( jointPositionsDefault_[jointNametoJointId_[jointName]] );
      jointPositionLimitsLow_.push_back(joint->limits->lower);
      jointPositionLimitsHigh_.push_back( joint->limits->upper);
      jointTorqueLimits_.push_back( joint->limits->effort);
      jointVelocityLimits_.push_back( joint->limits->velocity);
    }
  }

  void AracGazeboPlugin::initPublishers()  {
    // Actuator readings.
    std::cout << "Initializing Publishers"<< std::endl;

    // Joint State Publishers


    // Base State Publisher


    // Actuator Readings Publisher

  }

  void AracGazeboPlugin::initSubscribers()  {
    // Actuator readings.
    std::cout << "Initializing Publishers"<< std::endl;

    // Actuator Command Subscriber

    

  }


  GZ_REGISTER_MODEL_PLUGIN(AracGazeboPlugin)
}
