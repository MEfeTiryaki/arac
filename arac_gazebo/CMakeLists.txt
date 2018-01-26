cmake_minimum_required(VERSION 2.8.3)
project(arac_gazebo)

add_definitions(-std=c++11)

find_package(catkin REQUIRED
  COMPONENTS
    param_io
    arac_msgs
    gazebo_plugins
    gazebo_ros
    gazebo_worlds
    roscpp
    urdf
    xacro
)

find_package(gazebo REQUIRED)
find_package(Boost REQUIRED)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)
link_directories(
  ${GAZEBO_LIBRARY_DIRS}
)

catkin_package(
  INCLUDE_DIRS
    include
    ${GAZEBO_INCLUDE_DIRS}
  LIBRARIES
    ${PROJECT_NAME}
  CATKIN_DEPENDS
    param_io
    arac_msgs
    gazebo_plugins
    gazebo_ros
    gazebo_worlds
    roscpp
    urdf
    xacro
  DEPENDS
    Boost

)

add_library(
  ${PROJECT_NAME}
  src/AracGazeboPlugin.cpp
)
add_dependencies(
  ${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY config launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(FILES Readme.md
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
