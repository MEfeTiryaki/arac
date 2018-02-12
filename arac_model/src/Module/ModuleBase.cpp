/*
 name : ModuleBase.cpp
 Author : Selçuk Ercan , M. Efe Tiryaki

*/

#include "arac_model/Module/ModuleBase.hpp"

namespace kuco {

// Note : param_io is needed to use the getParam
using namespace param_io;

// Default Consructor Definition
ModuleBase::ModuleBase()
{
}

// Default Destructor Definition
ModuleBase::~ModuleBase()
{
}
void ModuleBase::initilize(){
}

void ModuleBase::create(){
}

void ModuleBase::advance(){
}

void ModuleBase::getDesiredState(){
  // pointer from Desired Value proivided by Trajectory Generator
  // XXX: Bunlar direk message'lardan alınmayack mı?
}
void ModuleBase::getMeasuredState(){
  // pointer from Desired Value proivided by Trajectory Generator
  // XXX: Bunlar direk message'lardan alınmayack mı?
}


} /* namespace kuco*/
