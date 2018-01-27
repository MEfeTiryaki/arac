/*
 Author : M. Efe Tiryaki
 */

#pragma once

// c++
#include <chrono>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <atomic>
#include <condition_variable>

// required for std::this_thread
#include <thread>

// gazebo
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>

// ros
#include <ros/ros.h>
#include <ros/callback_queue.h>
// geometry msgs
#include <geometry_msgs/WrenchStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistWithCovarianceStamped.h>

// sensor msgs
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/JointState.h>

#include "arac_msgs/AracState.h"

// urdf
#include <urdf/model.h>

namespace gazebo {
class AracGazeboPlugin : public ModelPlugin
{
 public:
  // Constructor.
  AracGazeboPlugin();

  // Destructor.
  virtual ~AracGazeboPlugin();

  // Implements Gazebo virtual load function.
  virtual void Load(physics::ModelPtr model, sdf::ElementPtr sdf);

  // Overrides Gazebo init function.
  virtual void Init();

  // Overrides Gazebo reset function.
  virtual void Reset();

  virtual void OnUpdate();
 protected:
  // Reads parameters from the parameter server.
  void readParameters(sdf::ElementPtr sdf);

  void initJointStructures();

  void initSubscribers();
  // Inits the ROS publishers.
  void initPublishers();
  // Inits the ROS services.
  void initServices();

  // Reads simulation state.
  virtual void readSimulation();

  // Writes simulation state.
  virtual void writeSimulation();

  // Retrieves URDF robot description from ROS parameter server.
  virtual std::string getUrdfRobotDescription(const std::string& paramName) const;

  // Ros node
  ros::NodeHandle* nodeHandle_;
  // Ensures gazebo methods are called sequentially
  std::recursive_mutex gazeboMutex_;

  // Name of the robot.
  std::string robotName_;
  // ROS robot description parameter name.
  std::string robotDescriptionParamName_;
  // Robot base link.
  std::string robotBaseLink_;
  // ROS robot description URDF string.
  std::string robotDescriptionUrdfString_;
  // ROS robot description URDF model.
  urdf::Model robotDescriptionUrdfModel_;

  // Frame names.
  std::string frameBase_;
  std::string frameOdometry_;
  std::string frameWorld_;
  std::string frameWorldGravityAligned_;

  // Gazebo time step.
  double gazeboTimeStep_ = 0.0;
  // Time step for publishing simulation state.
  double publishingTimeStep_ = 0.0;
  // Simulation time stamp taken at the start of the last updateCb() function call.
  common::Time lastStartUpdateSimTime_;
  // System time stamp taken at the start of the last updateCb() function call.
  std::chrono::time_point<std::chrono::steady_clock> lastStartUpdateSysTime_;
  // Current inter-update simulation time step.
  double updateSimTimeStep_ = 0.0;

  // Model.
  physics::ModelPtr model_;
  // World update event.
  event::ConnectionPtr updateConnection_;

  // Robot base link pose (transforms vectors from base to world).
  math::Pose robotBaseLinkPose_;
  // Robot base link linear velocity in world frame.
  math::Vector3 robotBaseLinkLinearVelocity_;
  // Robot base link angular velocity in base frame.
  math::Vector3 robotBaseLinkAngularVelocity_;

  // Publisher
  ros::Publisher robotStatePublisher_ ;
  ros::Publisher imuDataPublisher_ ;
  ros::Publisher actuatorDataPublisher_;

  // Estimator Bool
  bool isEstimatorUsed ;
  // Actuators
  std::vector<std::string> jointNames_;
  std::unordered_map<std::string, int> jointNametoJointId_;
  std::vector<gazebo::physics::JointPtr> jointPtrs_;
  std::vector<int> jointTypes_;
  std::vector<double> jointPositionsReset_;
  std::vector<double> jointPositionLimitsLow_;
  std::vector<double> jointPositionLimitsHigh_;
  std::vector<double> jointTorqueLimits_;
  std::vector<double> jointVelocityLimits_;
  std::vector<double> jointPositionsDefault_;



};

}
