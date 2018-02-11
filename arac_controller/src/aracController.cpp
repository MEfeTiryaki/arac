// arac gazebo
#include "arac_controller/aracController.hpp"
#include <param_io/get_param.hpp>

namespace kuco {

// Note : param_io is needed to use the getParam
using namespace param_io;

// Todo : make controllerInput length adjustable
aracController::aracController(kuco::State& state) :
  controllerInput_(4),
  state_(state)
{
}

aracController::~aracController()
{
}

void aracController::initilize( )
{

}

void aracController::advance(){
    setActuatorCommand();
}

void aracController::readParameters()
{

}


void aracController::setActuatorCommand(){

  double linearVelocity = state_.getLinearVelocityInX();
  double angularVelocity = state_.getAngularVelocityInZ();

  controllerInput_[0] = linearVelocity + angularVelocity ;
  controllerInput_[1] = linearVelocity + angularVelocity ;
  controllerInput_[2] = linearVelocity - angularVelocity ;
  controllerInput_[3] = linearVelocity - angularVelocity ;

}

std::vector<double> aracController::getControlInputs(){
  return controllerInput_;
}



} /* namespace kuco*/
