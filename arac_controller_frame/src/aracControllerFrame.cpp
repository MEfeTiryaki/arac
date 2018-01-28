// arac gazebo
#include "arac_controller_frame/aracControllerFrame.hpp"

namespace arac_controller_frame {

// Note : param_io is needed to use the getParam
using namespace param_io;
aracControllerFrame::aracControllerFrame()
{
}

aracControllerFrame::~aracControllerFrame()
{
}

void aracControllerFrame::init(int argc, char **argv)
{
  jointNames_.push_back("LF_WH");
  jointNames_.push_back("RF_WH");
  jointNames_.push_back("LH_WH");
  jointNames_.push_back("RH_WH");
  jointPositions_ = std::vector<double> (4, 0.0);
  jointVelocities_ = std::vector<double> (4, 0.0);
  jointEffort_ = std::vector<double> (4, 0.0);
  createActuatorCommand();

  nodeName_ = "/arac_controller_frame";

  ros::init(argc, argv, nodeName_);

  nodeHandle_ = new ros::NodeHandle("~");

  loop_rate_= new ros::Rate(400);

  initilizePublishers();
  initilizeSubscribers();

  joystickCommandStartTime_ = ros::Time::now().toSec();
  std::cout << "arac_controller_frame::init " << std::endl;

}

void aracControllerFrame::update()
{
}

void aracControllerFrame::execute()
{
  while (ros::ok()) {

    if (ros::Time::now().toSec()-joystickCommandStartTime_>0.5){
      resetActuatorCommand();
    }else{
      setActuatorCommand();
    }

    actuatorCommandPublisher_.publish(actuatorCommand_);

    ros::spinOnce();
    loop_rate_->sleep();
  }
}

void aracControllerFrame::initilizePublishers()
{
  std::cout << "arac_controller_frame::initilizePublishers" << std::endl;
  actuatorCommandPublisher_ = nodeHandle_->advertise < arac_msgs::ActuatorCommands
      > (nodeName_ + "/ActuatorCommands", 1);

}

// Todo : checkque size
void aracControllerFrame::initilizeSubscribers()
{
  std::cout << "arac_controller_frame::initilizeSubscribers" << std::endl;

  const std::string topicName = "/turtle1/cmd_vel";
  joystickSubscriber_ = nodeHandle_->subscribe(topicName, 10,
                                               &aracControllerFrame::getJoystickTwistInput, this);
}

void aracControllerFrame::getJoystickTwistInput(geometry_msgs::Twist msg)
{
  joystickTwistInput_ = msg;
  //joystickCommandStartTime_ = ros::Time::now();
  joystickCommandStartTime_ = ros::Time::now().toSec();
}

void aracControllerFrame::createActuatorCommand(){
  actuatorCommand_.inputs.name = jointNames_;
  actuatorCommand_.inputs.position = jointVelocities_;
  actuatorCommand_.inputs.velocity = jointVelocities_;
  actuatorCommand_.inputs.effort = jointEffort_;

}
void aracControllerFrame::resetActuatorCommand(){
  actuatorCommand_.inputs.velocity = std::vector<double> (4, 0.0);

}
void aracControllerFrame::setActuatorCommand(){
  double linearVelocity = joystickTwistInput_.linear.x;
  double angularVelocity = joystickTwistInput_.angular.z;
  actuatorCommand_.inputs.velocity[0] = linearVelocity + angularVelocity ;
  actuatorCommand_.inputs.velocity[1] = linearVelocity - angularVelocity ;
  actuatorCommand_.inputs.velocity[2] = linearVelocity + angularVelocity ;
  actuatorCommand_.inputs.velocity[3] = linearVelocity - angularVelocity ;
}
} /* namespace arac_controller_frame*/
