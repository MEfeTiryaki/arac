#pragma once

#include <ros/ros.h>

// *** Şuursuzca bıraktım şu kütüphaneleri

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

// ***

namespace arac_model {

class moduleBase
{
 public:
  // Constructor.
  moduleBase();

  // Destructor.
  virtual ~moduleBase();

  // Init
  virtual void init(int argc, char **argv);

  // Create
  virtual void create();

  // Advance
  virtual void advance();

 protected:
  virtual void getDesiredState();
  virtual void getMeasuredState();

 private:
  //XXX Bu ünite Trajectory Generator'dan veri alacak. Ondan bi pointer almak lazım olabilir.
  ros::NodeHandle* nodeHandle_; // Bu standart bir şey sanırım?
  ros::Rate* loop_rate_; // Advance fomksiyonu için mi buna ihtiyaç var?

  std::string nodeName_;
  std::string robotName_;

  double joystickCommandStartTime_;

  std::vector<double> measuredState;
  std::vector<double> desiredState;

  // Publishers --------------------------------------------------------------
  ros::Publisher actuatorCommandPublisher_;
  // Publisher names
  std::string actuatorCommandPublisherName_;
  // Publisher queue_size
  int actuatorCommandPublisherQueueSize_;
  // Publisher msgs
  arac_msgs::ActuatorCommands actuatorCommand_;

  // Subscriber
  ros::Subscriber joystickSubscriber_;
  // Subscriber names
  std::string joystickSubscriberName_;
  // Subscriber queue_size
  int joystickSubscriberQueueSize_;
  // Subscriber msgs
  geometry_msgs::Twist joystickMsg_;
};
}
