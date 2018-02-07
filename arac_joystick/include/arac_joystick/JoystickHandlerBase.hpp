/*
 * joystickHandlerBase.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: efe
 */

#include <ros/ros.h>

// ROS messages / services
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <std_srvs/Empty.h>
#include <std_msgs/Empty.h>


class JoystickHandlerBase{
 public :
  virtual JoystickHandlerBase();

  virtual ~JoystickHandlerBase();

  virtual void init();

  virtual void advance();

  virtual void readParameters();

 private:
   virtual void initilizeSubscribers();

   virtual void getJoystickMsg(geometry_msgs::Twist msg);


   ros::NodeHandle* nodeHandle_;
   ros::Rate* loop_rate_;


   // Subscriber
   ros::Subscriber joystickSubscriber_;
   // Subscriber names
   std::string joystickSubscriberName_;
   // Subscriber queue_size
   int joystickSubscriberQueueSize_;
   // Subscriber msgs
   geometry_msgs::Twist joystickMsg_;


   double joystickCommandStartTime_;



};
