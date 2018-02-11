cmake_minimum_required(VERSION 2.8.3)
project(arac_sim)

find_package(catkin REQUIRED
  COMPONENTS
    arac_description
    arac_gazebo
)

catkin_package(
  INCLUDE_DIRS
  CATKIN_DEPENDS
    arac_description
    arac_gazebo
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
)
