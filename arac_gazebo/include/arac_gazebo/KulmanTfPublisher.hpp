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

namespace kuco {

class KulmanTfPublisher
{
 public:
   KulmanTfPublisher();

   ~KulmanTfPublisher();

   void init();
   
   void execute();



 private:
   ros::NodeHandle* nodeHandle_;

   ros::Rate* loop_rate_;



};
}
