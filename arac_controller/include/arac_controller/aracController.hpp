#pragma once

#include "State.hpp"
#include <vector>

namespace kuco {

class aracController
{
 public:
  // Constructor.
  aracController(kuco::State& state);

  // Destructor.
  virtual ~aracController();

  // Init
  virtual void initilize();

  // Parameters init
  virtual void readParameters();

  // excute
  virtual void advance();

  virtual std::vector<double> getControlInputs();


 protected:

  virtual void setActuatorCommand();

 private:
   kuco::State& state_;

   std::vector<double> controllerInput_;


};

} /* namespace kuco*/
