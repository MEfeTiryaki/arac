/*
 name : KulmanModel.cpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/


#include "arac_model/Model/KulmanModel.hpp"

namespace kuco {

// Note : param_io is needed to use the getParam

KulmanModel::KulmanModel():
    govde_()
{
}

KulmanModel::~KulmanModel()
{
}

void KulmanModel::initilize()
{
}

void KulmanModel::create()
{
}

void KulmanModel::advance()
{
}

void KulmanModel::reset()
{
}

void KulmanModel::setGovde(Govde* govde)
{
  govde_ = govde;
}
Govde& KulmanModel::getGovde()
{
  return *govde_;
}

}; /* namespace arac_controller_frame*/
