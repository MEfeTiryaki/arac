/*
 name : AracModel.hpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#pragma once

#include "arac_model/Model/KulmanModel.hpp"
#include "arac_model/Module/Wheel.hpp"
#include <vector>

namespace kuco {

class AracModel : public KulmanModel
{
 public:
  AracModel();

  virtual ~AracModel();

  virtual void initilize();

  virtual void create();

  virtual void advance(double dt);

  virtual void reset();

  //void setWheel(Wheel Wheel);

  std::vector<Wheel*>& getWheel();


 protected:

  // vector içinde pointer ne kadar doğru bir yaklaşım emin değilim ama dursun
  Wheel* WheelLF_;
  Wheel* WheelRF_;
  Wheel* WheelLH_;
  Wheel* WheelRH_;

  std::vector<Wheel*>* Wheels_;
};

} /* namespace kuco */
