cmake_minimum_required(VERSION 2.8.3)
project(arac_model)

add_definitions("-std=c++11")

find_package(catkin REQUIRED
  COMPONENTS
)

# to use eigen library
find_package(Eigen3 REQUIRED)

catkin_package(
  INCLUDE_DIRS
  	include
    ${EIGEN3_INCLUDE_DIR}
  LIBRARIES
   arac_model
  CATKIN_DEPENDS
)


include_directories(
  include
	${EIGEN3_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
)
add_library(
  ${PROJECT_NAME}
	# State
  src/State/State.cpp
	# Model
  src/Model/KulmanModel.cpp
  src/Model/aracModel.cpp
	# Module
  src/Module/ModuleBase.cpp
  src/Module/Govde.cpp
  src/Module/Tekerlek.cpp

)

add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)
