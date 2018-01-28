#pragma once

#include <ros/ros.h>

// ROS messages / services
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <std_msgs/Empty.h>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <memory>
#include <mutex>

#include <param_io/get_param.hpp>


#include "arac_msgs/ActuatorCommands.h"

namespace arac_controller_frame {

class aracControllerFrame
{
 public:
  // Constructor.
  aracControllerFrame();

  // Destructor.
  virtual ~aracControllerFrame();

  // Init
  virtual void init(int argc, char **argv);

  // Update
  virtual void update();

  // excute
  virtual void execute();

 protected:
  virtual void initilizePublishers();

  virtual void initilizeSubscribers();

  virtual void getJoystickTwistInput(geometry_msgs::Twist msg);

  virtual void setActuatorCommand();

  void createActuatorCommand();

  void resetActuatorCommand();
 private:

  ros::NodeHandle* nodeHandle_;

  ros::Rate* loop_rate_;

  std::string nodeName_;
  std::string robotName_;

  geometry_msgs::Twist joystickTwistInput_;
  double joystickCommandStartTime_;

  ros::Publisher actuatorCommandPublisher_;
  arac_msgs::ActuatorCommands actuatorCommand_;


  ros::Subscriber joystickSubscriber_;

  std::vector<std::string> jointNames_;
  std::vector<double> jointPositions_;
  std::vector<double> jointVelocities_;
  std::vector<double> jointEffort_;


};
}
