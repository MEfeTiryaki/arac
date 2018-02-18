#include <ros/ros.h>
#include <iostream>

#include "arac_state_estimator/StateEstimator.hpp"


int main(int argc, char **argv)
{
  arac_state_estimator::StateEstimator estimator = arac_state_estimator::StateEstimator();
  estimator.create();
  estimator.initilize(argc,argv);
  estimator.execute();
  return 0;
}
