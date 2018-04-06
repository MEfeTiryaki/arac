#pragma once

#include "arac_model/State/State.hpp"
#include "arac_model/Model/AracModel.hpp"
#include <vector>


namespace kuco {

class aracPidController
{
 public:
  // Constructor.
//  aracController(kuco::State& state);
  aracPidController(kuco::AracModel& model);

  // Destructor.
  virtual ~aracPidController();

  // Init
  virtual void initilize();

  // Parameters init
  virtual void readParameters();

  // excute
  virtual void advance();


 protected:

  virtual void setActuatorCommand();

 private:
   //kuco::State& state_;
   kuco::AracModel model_;


};

} /* namespace kuco*/
