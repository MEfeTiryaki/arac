// arac gazebo
#include "arac_controller/aracPidController.hpp"
#include <param_io/get_param.hpp>

namespace kuco {

// Note : param_io is needed to use the getParam
using namespace param_io;

// Todo : make controllerInput length adjustable
aracPidController::aracPidController(kuco::AracModel& model)
    : model_(model)
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

  std::vector<double> controllerInput(4);
  controllerInput[0] = (desLinearVelocity-measLinearVelocity) + (desAngularVelocity-measAngularVelocity);
  controllerInput[1] = (desLinearVelocity-measLinearVelocity) + (desAngularVelocity-measAngularVelocity);
  controllerInput[2] = (desLinearVelocity-measLinearVelocity) - (desAngularVelocity-measAngularVelocity);
  controllerInput[3] = (desLinearVelocity-measLinearVelocity) - (desAngularVelocity-measAngularVelocity);


  auto& wheels = model_.getTekerlek();

  // Todo (Efe Tiryaki 16.02.18): 4 yerine teker sayısını çek
  for (int i = 0; i < 4; i++) {
    kuco::AngularVelocity input;
    input << 0.0, 0.0, controllerInput[i];
    wheels[i]->getDesiredState().setAngularVelocityInWorldFrame(input);
  }
}

} /* namespace kuco*/
