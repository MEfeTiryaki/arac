#pragma once

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
#include <vector>

#include <param_io/get_param.hpp>

#include "kulman_controller_frame/KulmanControllerFrame.hpp"
#include "kulman_joystick/JoystickAcc.hpp"
#include "arac_controller/AracOLController.hpp"
#include "kulman_msgs/ActuatorCommands.h"
#include "arac_model/AracModel.hpp"
#include "arac_state_estimator/AracStateEstimatorHandler.hpp"

// stl
#include <memory>

namespace kuco {

using KulmanModel_ = kuco::AracModel;
using Controller_ = kuco::AracOLController;
using EstimatorHandler_ = estimator::AracStateEstimatorHandler;
using Joystick_ = joystick::JoystickAcc<KulmanModel_>;

class AracControllerFrame : public KulmanControllerFrame<KulmanModel_,Controller_,EstimatorHandler_,Joystick_>
{
 public:
  // Constructor.
  AracControllerFrame();

  // Destructor.
  virtual ~AracControllerFrame();

  // Init
  virtual void initilize(int argc, char **argv) override;

  virtual void create() override ;

 protected:

  void setActuatorCommand() override;

};

}
