

#include <arac_state_estimator/AracStateEstimator.hpp>
#include <ros/ros.h>
#include <iostream>

#include "arac_model/Model/AracModel.hpp"


int main(int argc, char **argv)
{
  estimator::AracStateEstimator estimator_ = estimator::AracStateEstimator();
  estimator_.create();
  estimator_.initilize(argc,argv);
  estimator_.execute();
  return 0;
}
