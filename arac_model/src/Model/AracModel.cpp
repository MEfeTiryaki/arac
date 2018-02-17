/*
 name : AracModel.cpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#include "arac_model/Model/AracModel.hpp"

namespace kuco {

// Note : param_io is needed to use the getParam

AracModel::AracModel()
    : tekerlekLF_(new Tekerlek()),
      tekerlekRF_(new Tekerlek()),
      tekerlekLH_(new Tekerlek()),
      tekerlekRH_(new Tekerlek()),
      tekerlekler_(new std::vector<Tekerlek*>())
{
  tekerlekler_->push_back(tekerlekLF_);
  tekerlekler_->push_back(tekerlekRF_);
  tekerlekler_->push_back(tekerlekLH_);
  tekerlekler_->push_back(tekerlekRH_);
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

void AracModel::advance()
{
}

void AracModel::reset()
{
}

//void AracModel::setTekerlekler(std::vector<Tekerlek>& tekerlek)
//{
//  tekerlekler_= tekerlek;
//}
//std::vector<Tekerlek>& AracModel::getTekerlekler()
//{
//  return *tekerlekler_;
//}

std::vector<Tekerlek*>& AracModel::getTekerlek()
{
  return *tekerlekler_;
}

} /* namespace arac_controller_frame*/
