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
 #include <std_msgs/Empty.h>

 #include <boost/thread.hpp>
 #include <boost/chrono.hpp>
 #include <memory>
 #include <mutex>

 #include "arac_model/State/State.hpp"

namespace joystick {

  class JoystickHandlerBase{
    public:
      JoystickHandlerBase(kuco::State& state);

      virtual ~JoystickHandlerBase();

      virtual void initilize(ros::NodeHandle* nh);

      virtual void advance();

      virtual void readParameters();

      double getLinearVelocity(){ return linVelocity_ ; };

      double getAngularVelocity(){ return angVelocity_ ; };
    protected:
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

      double linVelocity_;
      double angVelocity_;

      kuco::State& state_;
  };

}
