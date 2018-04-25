

#include <kulman_state_estimator/StateEstimatorNode.hpp>
#include <arac_state_estimator/AracEKF.hpp>
#include <arac_model/AracModel.hpp>


#include <ros/ros.h>
#include <iostream>

int main(int argc, char **argv)
{
  estimator::StateEstimatorNode<kuco::AracModel,estimator::AracEKF> estimator_ = estimator::StateEstimatorNode<kuco::AracModel,estimator::AracEKF>();
  estimator_.create();
  estimator_.initilize(argc,argv);
  estimator_.execute();
  return 0;
}
