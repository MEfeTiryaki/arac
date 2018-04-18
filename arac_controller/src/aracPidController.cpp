// arac gazebo
#include "arac_controller/aracPidController.hpp"
#include <param_io/get_param.hpp>

namespace kuco {

// Note : param_io is needed to use the getParam
using namespace param_io;

// Todo : make controllerInput length adjustable
aracPidController::aracPidController(kuco::AracModel& model)
    : model_(model),
      rWheel_(0.15)
{
}

aracPidController::~aracPidController()
{
}

void aracPidController::initilize()
{

}

void aracPidController::advance()
{
  setActuatorCommand();
}

void aracPidController::readParameters()
{

}

void aracPidController::setActuatorCommand()
{
  double measLinearVelocity = model_.getGovde().getMeasuredState().getVelocityInWorldFrame()[0];
  double measAngularVelocity = model_.getGovde().getMeasuredState().getAngularVelocityInWorldFrame()[2];

  double desLinearVelocity = model_.getGovde().getDesiredState().getVelocityInWorldFrame()[0];
  double desAngularVelocity = model_.getGovde().getDesiredState().getAngularVelocityInWorldFrame()[2];

  std::cout << "Linear des/meas: " <<  desLinearVelocity <<" , " << measLinearVelocity << std::endl;
  std::cout << "Angula des/meas: " <<  desAngularVelocity <<" , " << measAngularVelocity << std::endl;

  std::vector<double> controllerInput(4);
  controllerInput[0] = (-(desLinearVelocity-measLinearVelocity) + (desAngularVelocity-measAngularVelocity))/rWheel_;
  controllerInput[1] = (-(desLinearVelocity-measLinearVelocity) + (desAngularVelocity-measAngularVelocity))/rWheel_;
  controllerInput[2] = (-(desLinearVelocity-measLinearVelocity) - (desAngularVelocity-measAngularVelocity))/rWheel_;
  controllerInput[3] = (-(desLinearVelocity-measLinearVelocity) - (desAngularVelocity-measAngularVelocity))/rWheel_;

  std::cout << "Left  : " <<  controllerInput[0] << std::endl;
  std::cout << "Right : " <<  controllerInput[2] << std::endl;


  auto& wheels = model_.getTekerlek();

  // Todo (Efe Tiryaki 16.02.18): 4 yerine teker sayısını çek
  for (int i = 0; i < 4; i++) {
    kuco::AngularVelocity input;
    input << 0.0, 0.0, controllerInput[i];
    wheels[i]->getDesiredState().setAngularVelocityInWorldFrame(input);
  }
}

} /* namespace kuco*/
