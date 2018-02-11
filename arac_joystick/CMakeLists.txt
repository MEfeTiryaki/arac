cmake_minimum_required(VERSION 2.8.3)
project(arac_joystick)

add_definitions("-std=c++11")

find_package(catkin REQUIRED
  COMPONENTS
  roscpp
  param_io
  geometry_msgs
  std_msgs
  sensor_msgs
)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    arac_joystick
  CATKIN_DEPENDS
    roscpp
    param_io
    geometry_msgs
    std_msgs
    sensor_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library( ${PROJECT_NAME}
  src/JoystickHandlerBase.cpp
  src/JoystickDummy.cpp
)

add_dependencies(arac_joystick
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(arac_joystick
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)
