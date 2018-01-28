#pragma once

#include <ros/ros.h>

// ROS messages / services
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <std_srvs/Empty.h>
#include <std_msgs/Empty.h>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <memory>
#include <mutex>

#include <param_io/get_param.hpp>

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

 private:

  ros::NodeHandle* nodeHandle_;

  std::string nodeName_;

  geometry_msgs::TwistStamped joystickTwistInput_;

  ros::Publisher actuatorCommandPublisher_;

  ros::Subscriber joystickSubscriber_;

};
}
