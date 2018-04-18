// arac gazebo
#include "arac_controller_frame/AracControllerFrame.hpp"

namespace kuco {

// Note : param_io is needed to use the getParam
using namespace param_io;
AracControllerFrame::AracControllerFrame():
    KulmanControllerFrame<KulmanModel_,Controller_,Estimator_,Joystick_>()
{

}

AracControllerFrame::~AracControllerFrame()
{
}

void AracControllerFrame::create()
{
  this->model_ = new kuco::AracModel;
  this->estimator_ = new estimator::AracEKF(*model_);
  this->joystickHandler_ = new joystick::JoystickAcc<kuco::AracModel>(*model_);
  this->controller_ = new kuco::AracOLController(*model_);
}

void AracControllerFrame::initilize(int argc, char **argv)
{
  // nodeHandler olusturuldu.
  this->nodeName_ = "/arac_controller_frame";
  ros::init(argc, argv, nodeName_);
  this->nodeHandle_ = new ros::NodeHandle("~");

  // Parametreler okundu.
  readParameters();

  // loop rate ayarlandi
  this->loop_rate_ = new ros::Rate(loopFrequency_);

  this->jointPositions_ = std::vector<double>(n_, 0.0);
  this->jointVelocities_ = std::vector<double>(n_, 0.0);
  this->jointEffort_ = std::vector<double>(n_, 0.0);
  createActuatorCommand();

  initilizePublishers();
  initilizeSubscribers();

  this->model_->initilize();
  this->joystickHandler_->initilize(nodeHandle_);
  this->estimator_->initilize(nodeHandle_);
  this->controller_->initilize();

  print();
}

void AracControllerFrame::setActuatorCommand()
{
  double wheelVelocities;
  auto& wheels = this->model_->getWheel();
  for (int i = 0; i < actuatorCommand_.inputs.velocity.size(); i++) {
    wheelVelocities = wheels[i]->getDesiredState().getAngularVelocityInWorldFrame()[2];
    this->actuatorCommand_.inputs.velocity[i] = wheelVelocities;
  }
}


} /* namespace kuco*/
