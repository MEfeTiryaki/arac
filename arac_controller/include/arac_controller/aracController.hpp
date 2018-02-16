#pragma once

#include "arac_model/State/State.hpp"
#include "arac_model/Model/AracModel.hpp"
#include <vector>


namespace kuco {

class aracController
{
 public:
  // Constructor.
//  aracController(kuco::State& state);
  aracController(kuco::AracModel& model);

  // Destructor.
  virtual ~aracController();

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
