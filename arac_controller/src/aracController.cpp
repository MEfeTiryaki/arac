// arac gazebo
#include "arac_controller/aracController.hpp"
#include <param_io/get_param.hpp>

namespace kuco {

// Note : param_io is needed to use the getParam
using namespace param_io;

// Todo : make controllerInput length adjustable
aracController::aracController(kuco::AracModel& model)
    : model_(model)
{
}

aracController::~aracController()
{
}

void aracController::initilize()
{

}

void aracController::advance()
{
  setActuatorCommand();
}

void aracController::readParameters()
{

}

void aracController::setActuatorCommand()
{

  double linearVelocity = model_.getGovde().getDesiredState().getVelocityInWorldFrame()[0];
  double angularVelocity = model_.getGovde().getDesiredState().getAngularVelocityInWorldFrame()[2];

  std::vector<double> controllerInput(4);
  controllerInput[0] = linearVelocity + angularVelocity;
  controllerInput[1] = linearVelocity + angularVelocity;
  controllerInput[2] = linearVelocity - angularVelocity;
  controllerInput[3] = linearVelocity - angularVelocity;

  auto& tekerler = model_.getTekerlek();

  // Todo (Efe Tiryaki 16.02.18): 4 yerine teker sayısını çek
  for (int i = 0; i < 4; i++) {
    kuco::AngularVelocity input;
    input << 0.0, 0.0, controllerInput[i];
    tekerler[i]->getDesiredState().setAngularVelocityInWorldFrame(input);
  }
}

} /* namespace kuco*/
