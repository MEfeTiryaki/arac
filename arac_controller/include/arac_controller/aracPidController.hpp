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
  virtual void advance(double dt);


 protected:

  virtual void setActuatorCommand();

 private:
   //kuco::State& state_;
   kuco::AracModel model_;

   double rWheel_;



   double n_ ;
   double l_ ;

   Eigen::VectorXd X_;
   Eigen::VectorXd U_;

   Eigen::Matrix A_ ;
   Eigen::Matrix B_ ;

   Eigen::Matrix K_ ;
};

} /* namespace kuco*/
