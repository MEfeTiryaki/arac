cmake_minimum_required(VERSION 2.8.3)
project(arac_model)

add_definitions("-std=c++11")

find_package(catkin REQUIRED
  COMPONENTS
)

catkin_package(
  INCLUDE_DIRS
  	include
  LIBRARIES
   arac_model
  CATKIN_DEPENDS
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
add_library(
  ${PROJECT_NAME}
  src/State.cpp
)

add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)
