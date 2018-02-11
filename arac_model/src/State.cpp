
#include "State.hpp"

namespace kuco{

// Todo : check if we can add robot name here
State::State()
{
  linearVelocityInX_ = 0.0 ;
  angularVelocityInZ_= 0.0 ; 
}

State::~State()
{
}

}/* namespace kuco*/
