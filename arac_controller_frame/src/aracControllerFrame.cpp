// arac gazebo
#include "arac_controller_frame/aracControllerFrame.hpp"

namespace arac_controller_frame {

// Note : param_io is needed to use the getParam
using namespace param_io;
aracControllerFrame::aracControllerFrame(){

}

aracControllerFrame::~aracControllerFrame()
{
}

void aracControllerFrame::create(){
  state_ = new kuco::State();
  joystickHandler_ = new joystick::JoystickDummy(*state_);
  controller_ =  new kuco::aracController(*state_);
}

void aracControllerFrame::initilize(int argc, char **argv)
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

  loop_rate_= new ros::Rate(100);

  readParameters();
  initilizePublishers();
  initilizeSubscribers();

  joystickHandler_->initilize( nodeHandle_);
  controller_->initilize();

  std::cout << "arac_controller_frame::init " << std::endl;
}

void aracControllerFrame::update()
{

}

void aracControllerFrame::execute()
{
  while (ros::ok()) {
    advance();
    ros::spinOnce();
    loop_rate_->sleep();
  }
}

void aracControllerFrame::advance(){

  // Estimator here in future

  // Advance the joystick handler
  joystickHandler_->advance();

  // Advance the controller
  controller_->advance();

  // set actuator commands
  setActuatorCommand();
  // publish actuators
  actuatorCommandPublisher_.publish(actuatorCommand_);


}

void aracControllerFrame::readParameters()
{
  // Get Publishers parameters
  getParam(*nodeHandle_, "publishers/actuator_commands/topic", actuatorCommandPublisherName_);
  getParam(*nodeHandle_, "publishers/actuator_commands/queue_size", actuatorCommandPublisherQueueSize_);

}


void aracControllerFrame::initilizePublishers(){
  std::cout << "arac_controller_frame::initilizePublishers" << std::endl;
  actuatorCommandPublisher_ = nodeHandle_->advertise < arac_msgs::ActuatorCommands>
                            ( actuatorCommandPublisherName_, actuatorCommandPublisherQueueSize_);

}

void aracControllerFrame::initilizeSubscribers()
{

}

void aracControllerFrame::createActuatorCommand(){
  actuatorCommand_.inputs.name = jointNames_;
  actuatorCommand_.inputs.position = jointVelocities_;
  actuatorCommand_.inputs.velocity = jointVelocities_;
  actuatorCommand_.inputs.effort = jointEffort_;

}

void aracControllerFrame::setActuatorCommand(){
  std::vector<double> wheelVelocities;

  wheelVelocities = controller_->getControlInputs();
  for(int i=0; i<actuatorCommand_.inputs.velocity.size(); i++)
    actuatorCommand_.inputs.velocity[i] = wheelVelocities[i];
}




} /* namespace arac_controller_frame*/
