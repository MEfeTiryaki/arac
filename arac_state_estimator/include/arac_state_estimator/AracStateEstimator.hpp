#include <ros/ros.h>

// ROS messages / services
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <std_msgs/Empty.h>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <memory>
#include <mutex>

#include "arac_model/State/State.hpp"
#include "arac_model/Model/AracModel.hpp"

#include "kulman_state_estimator/KulmanStateEstimatorBase.hpp"

namespace estimator {

using Model = kuco::AracModel ;

class AracStateEstimator : public KulmanStateEstimatorBase<Model>
{
 public:
  //JoystickHandlerBase(kuco::State& state);
  AracStateEstimator();

  virtual void initilize(int argc, char **argv) override ;

  virtual void create() override ;

  virtual void advance() override ;

  virtual void execute() override ;

  virtual void readParameters() override ;

 protected:
  virtual void initilizeSubscribers() override ;

  virtual void initilizePublishers() override ;

};

}
