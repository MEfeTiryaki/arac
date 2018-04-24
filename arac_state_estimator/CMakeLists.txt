cmake_minimum_required(VERSION 2.8.3)
project(arac_state_estimator)

add_definitions("-std=c++11")

find_package(catkin REQUIRED
  COMPONENTS
  kulman_state_estimator
  kulman_msgs
  arac_model
  roscpp
  param_io
  geometry_msgs
  std_msgs
  sensor_msgs


)


find_package(Eigen3 REQUIRED)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

catkin_package(
  INCLUDE_DIRS
    include
    ${catkin_INCLUDE_DIRS}
  LIBRARIES
    ${PROJECT_NAME}
  CATKIN_DEPENDS
    kulman_state_estimator
    kulman_msgs
 	  arac_model
    roscpp
    param_io
    geometry_msgs
    std_msgs
    sensor_msgs
  DEPENDS
)



add_library(
  ${PROJECT_NAME}
# Estimators
  src/AracPerfectEstimator.cpp
  src/AracEKF.cpp
# Handlers
  src/AracStateEstimatorHandler.cpp
)

add_dependencies(
  ${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)


add_dependencies(
  ${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)

add_executable(arac_state_estimator_node
  src/arac_state_estimator_node.cpp
)
add_dependencies(arac_state_estimator_node
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(arac_state_estimator_node
  arac_state_estimator
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)



#############
## Install ##
#############

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY config launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(FILES Readme.md
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
