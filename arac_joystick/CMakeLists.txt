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
  arac_model
)

# Attempt to find catkinized kindr
find_package(kindr QUIET)
if(NOT kindr_FOUND)
  # Attempt to find package-based kindr
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(kindr kindr REQUIRED)
endif()

find_package(Eigen3 REQUIRED)


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
    arac_model
  DEPENDS
    kindr
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${kindr_INCLUDE_DIRS}
)

add_library( ${PROJECT_NAME}
  src/JoystickHandlerBase.cpp
  src/JoystickDummy.cpp
)

add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
