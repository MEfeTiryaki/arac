cmake_minimum_required(VERSION 2.8.3)
project(arac_highlevel_controller)

add_definitions("-std=c++11")

find_package(catkin REQUIRED
  COMPONENTS
)

catkin_package(
  INCLUDE_DIRS
  CATKIN_DEPENDS
)

