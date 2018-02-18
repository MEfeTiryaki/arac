
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

namespace estimator {

class StateEstimator
{
 public:
  //JoystickHandlerBase(kuco::State& state);
  StateEstimator(kuco::AracModel& model);

  virtual ~StateEstimator();

  virtual void initilize(ros::NodeHandle* nh);

  virtual void advance();

  virtual void readParameters();

 protected:
  virtual void initilizeSubscribers();

  ros::NodeHandle* nodeHandle_;
  ros::Rate* loop_rate_;

  //kuco::State& state_;
  kuco::AracModel model_;
};

}
