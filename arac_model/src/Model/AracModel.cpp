/*
 name : AracModel.cpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#include "arac_model/Model/AracModel.hpp"

namespace kuco {

// Note : param_io is needed to use the getParam
AracModel::AracModel()
    : tekerlekler_()
{
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

void AracModel::setTekerlek(Tekerlek* tekerlek)
{
  tekerlekler_.push_back(tekerlek);
}

Tekerlek& AracModel::getTekerlek(int index)
{
  return *(tekerlekler_[index]);
}


} /* namespace arac_controller_frame*/
