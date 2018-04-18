cmake_minimum_required(VERSION 2.8.3)
project(arac)

add_definitions("-std=c++11")

find_package(catkin REQUIRED
  COMPONENTS
  arac_controller
  arac_controller_frame
  arac_description
  arac_gazebo
  #arac_joystick
  arac_model
  arac_msgs
  arac_sim
  arac_state_estimator
  arac_rviz
  param_io
)

catkin_package(
  INCLUDE_DIRS
  CATKIN_DEPENDS
  arac_controller
  arac_controller_frame
  arac_description
  arac_gazebo
  #arac_joystick
  arac_model
  arac_msgs
  arac_sim
  arac_state_estimator
  arac_rviz
  param_io
)
