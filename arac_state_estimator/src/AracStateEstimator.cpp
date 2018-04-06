#include "arac_state_estimator/AracStateEstimator.hpp"

namespace estimator {

AracStateEstimator::AracStateEstimator(Model& model)
    : KulmanStateEstimatorBase(model)
{

}

void AracStateEstimator::initilize(ros::NodeHandle* nh)
{
}

void AracStateEstimator::advance()
{
//  positionWorldToBase_[0] = kulmanStateMsg_.;
//  positionWorldToBase_[1] = kulmanStateMsg_.pose.pose.pos.y;
//  positionWorldToBase_[2] = kulmanStateMsg_.pose.pose.pos.z;
  positionWorldToBase_[0] = kulmanStateMsg_.pose.pose.position.x;
  positionWorldToBase_[1] = kulmanStateMsg_.pose.pose.position.y;
  positionWorldToBase_[2] = kulmanStateMsg_.pose.pose.position.z;

  orientationWorldToBase_[0] = kulmanStateMsg_.pose.pose.orientation.w;
  orientationWorldToBase_[1] = kulmanStateMsg_.pose.pose.orientation.x;
  orientationWorldToBase_[2] = kulmanStateMsg_.pose.pose.orientation.y;
  orientationWorldToBase_[3] = kulmanStateMsg_.pose.pose.orientation.z;

  velocityWorldToBaseInWorldFrame_[0] = kulmanStateMsg_.twist.twist.linear.x;
  velocityWorldToBaseInWorldFrame_[1] = kulmanStateMsg_.twist.twist.linear.y;
  velocityWorldToBaseInWorldFrame_[2] = kulmanStateMsg_.twist.twist.linear.z;

  angularVelocityWorldToBaseInWorldFrame_[0] = kulmanStateMsg_.twist.twist.angular.x;
  angularVelocityWorldToBaseInWorldFrame_[1] = kulmanStateMsg_.twist.twist.angular.y;
  angularVelocityWorldToBaseInWorldFrame_[2] = kulmanStateMsg_.twist.twist.angular.z;

  // Kestirilen konum,yönelim ve hızları ölçülen duruma ata.
  model_.getGovde().getMeasuredState().setPositionInWorldFrame(positionWorldToBase_);
  model_.getGovde().getMeasuredState().setOrientationInWorldFrame(orientationWorldToBase_);
  model_.getGovde().getMeasuredState().setVelocityInWorldFrame(velocityWorldToBaseInWorldFrame_);
  model_.getGovde().getMeasuredState().setAngularVelocityInWorldFrame(
      angularVelocityWorldToBaseInWorldFrame_);
}

}
