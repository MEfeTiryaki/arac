/*
 * StateEstimator.cpp
 *
 *  Created on: Feb 18, 2018
 *      Author: efe
 */





#include "arac_state_estimator/StateEstimator.hpp"

// Todo (Efe Tiryaki 16.02.18): State içinde tanımlanan Eigen::Vector lerini ayrı headera alınca bundan
// kurtul .
#include "arac_model/State/State.hpp"


#include <param_io/get_param.hpp>


// Note : param_io is needed to use the getParam

namespace estimator{

using namespace param_io;

//JoystickHandlerBase::JoystickHandlerBase(kuco::State& state)
//  : state_(state)
//{
//}
StateEstimator::StateEstimator(kuco::AracModel& model)
  : model_(model)
{
}

StateEstimator::~StateEstimator(){
}

void StateEstimator::initilize(ros::NodeHandle* nh )
{

  nodeHandle_ = nh ;

  readParameters();

  initilizeSubscribers();


}

void StateEstimator::advance()
{
  for(int i=0 ;i<5;i++){
    std::cout << "estimator : "<< i << std::endl;
  }
}

void StateEstimator::readParameters()
{
}

void StateEstimator::initilizeSubscribers()
{
}


}

