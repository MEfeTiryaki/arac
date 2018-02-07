

#include "arac_joystick/JoystickHandlerBase.hpp"

namespace gazebo {

// Note : param_io is needed to use the getParam
using namespace param_io;

// Todo : check if we can add robot name here
JoystickHandlerBase::JoystickHandlerBase()
{
}

JoystickHandlerBase::~JoystickHandlerBase()
{
}

void JoystickHandlerBase::init()
{
  ros::init(argc, argv, "joystick");
  nodeHandle_ = new ros::NodeHandle("~");
  loop_rate_= new ros::Rate(100);

  readParameters();

  initilizePublishers();
  initilizeSubscribers();

  joystickCommandStartTime_ = ros::Time::now().toSec();

}

void JoystickHandlerBase::advance()
{
}

void JoystickHandlerBase::readParameters(){
  // Get Subscriber parameters
  getParam(*nodeHandle_, "subscribers/joystick/topic", joystickSubscriberName_);
  getParam(*nodeHandle_, "subscribers/joystick/queue_size", joystickSubscriberQueueSize_);

}

void JoystickHandlerBase::initilizeSubscribers()
{
  joystickSubscriber_ = nodeHandle_->subscribe(joystickSubscriberName_, joystickSubscriberQueueSize_,
                                               &JoystickHandlerBase::getJoystickMsg, this);
}

void JoystickHandlerBase::getJoystickMsg(geometry_msgs::Twist msg)
{
  joystickMsg_ = msg;
  joystickCommandStartTime_ = ros::Time::now().toSec();
}
