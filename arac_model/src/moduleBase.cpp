// arac gazebo
#include "arac_model/ModuleBase.hpp"

namespace module_base {

// Note : param_io is needed to use the getParam
using namespace param_io;

// Default Consructor Definition
module_base::moduleBase()
{
}

// Default Destructor Definition
module_base::~moduleBase()
{
}

void moduleBase::init(int argc, char **argv){
  measuredState = std::vector<double>;
  desiredState = std::vector<double>;

  nodeName_ = "/module_base";

  ros::init(argc, argv, nodeName_);

  nodeHandle_ = new ros::NodeHandle("~");

  loop_rate_= new ros::Rate(400);

  readParameters();
  initilizePublishers();
  initilizeSubscribers();

  joystickCommandStartTime_ = ros::Time::now().toSec();
  std::cout << "module_base::init " << std::endl;
}

void moduleBase::create(){
}

void moduleBase::advance(){
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

void getDesiredState(){
  // pointer from Desired Value proivided by Trajectory Generator
  // XXX: Bunlar direk message'lardan alınmayack mı?
}
void getMeasuredState(){
  // pointer from Desired Value proivided by Trajectory Generator
  // XXX: Bunlar direk message'lardan alınmayack mı?
}

// PUBLISHER AND SUBSCRIBER
void moduleBase::readParameters(){
  // Get Publishers parameters
  getParam(*nodeHandle_, "publishers/actuator_commands/topic", actuatorCommandPublisherName_);
  getParam(*nodeHandle_, "publishers/actuator_commands/queue_size", actuatorCommandPublisherQueueSize_);

  // Get Subscriber parameters
  getParam(*nodeHandle_, "subscribers/joystick/topic", joystickSubscriberName_);
  getParam(*nodeHandle_, "subscribers/joystick/queue_size", joystickSubscriberQueueSize_);
}

void moduleBase::initilizePublishers(){
  std::cout << "arac_controller_frame::initilizePublishers" << std::endl;
  actuatorCommandPublisher_ = nodeHandle_->advertise < arac_msgs::ActuatorCommands>
                            ( actuatorCommandPublisherName_, actuatorCommandPublisherQueueSize_);
}
// TODO: checkque size
void moduleBase::initilizeSubscribers(){
  std::cout << "arac_controller_frame::initilizeSubscribers" << std::endl;

  joystickSubscriber_ = nodeHandle_->subscribe(joystickSubscriberName_, joystickSubscriberQueueSize_,
                                               &aracControllerFrame::getJoystickTwistInput, this);
}

// TODO: Trajectory Generator'dan oluşturulacak komutu alacak fn oluştur.
/***
void aracControllerFrame::getJoystickTwistInput(geometry_msgs::Twist msg){
  joystickMsg_ = msg;
  joystickCommandStartTime_ = ros::Time::now().toSec();
}
***/

} /* namespace arac_controller_frame*/
