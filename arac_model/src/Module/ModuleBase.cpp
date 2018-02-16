/*
 name : ModuleBase.cpp
 Author : Selçuk Ercan , M. Efe Tiryaki

 */

#include "arac_model/Module/ModuleBase.hpp"

namespace kuco {

// Note : param_io is needed to use the getParam
// Default Consructor Definition
ModuleBase::ModuleBase()
{
}

// Default Destructor Definition
ModuleBase::~ModuleBase()
{
}
void ModuleBase::initilize()
{
  desiredState_ =  State();
  measuredState_ =  State();
}

void ModuleBase::create()
{
}

void ModuleBase::advance()
{
}

void ModuleBase::setName(std::string name ){
  name_= name;
}
std::string ModuleBase::getName(){
  return name_;
}

State& ModuleBase::getDesiredState()
{
  return desiredState_;
}
State& ModuleBase::getMeasuredState()
{
  return measuredState_;
}

} /* namespace kuco*/
