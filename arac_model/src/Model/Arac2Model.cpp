/*
 name : AracModel.cpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#include "arac_model/Model/Arac2Model.hpp"

namespace kuco {

// Note : param_io is needed to use the getParam

Arac2Model::Arac2Model()
    : tekerlekL_(new Tekerlek()),
      tekerlekR_(new Tekerlek()),
      tekerlekler_(new std::vector<Tekerlek*>())
{
  tekerlekler_->push_back(tekerlekL_);
  tekerlekler_->push_back(tekerlekR_);
}

Arac2Model::~Arac2Model()
{
}

void Arac2Model::initilize()
{
}

void Arac2Model::create()
{
}

void Arac2Model::advance()
{
}

void Arac2Model::reset()
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

std::vector<Tekerlek*>& Arac2Model::getTekerlek()
{
  return *tekerlekler_;
}

} /* namespace */
