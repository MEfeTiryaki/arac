/*
 name : AracModel.cpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#include "arac_model/Model/AracModel.hpp"

namespace kuco {

// Note : param_io is needed to use the getParam

AracModel::AracModel()
    : WheelLF_(new Wheel()),
      WheelRF_(new Wheel()),
      WheelLH_(new Wheel()),
      WheelRH_(new Wheel()),
      Wheels_(new std::vector<Wheel*>())
{
  Wheels_->push_back(WheelLF_);
  Wheels_->push_back(WheelRF_);
  Wheels_->push_back(WheelLH_);
  Wheels_->push_back(WheelRH_);
}

AracModel::~AracModel()
{
}

void AracModel::initilize()
{
}

void AracModel::create()
{
}

void AracModel::advance(double dt)
{
}

void AracModel::reset()
{
}

//void AracModel::setWheeller(std::vector<Wheel>& Wheel)
//{
//  Wheeller_= Wheel;
//}
//std::vector<Wheel>& AracModel::getWheeller()
//{
//  return *Wheeller_;
//}

std::vector<Wheel*>& AracModel::getWheel()
{
  return *Wheels_;
}

} /* namespace arac_controller_frame*/
