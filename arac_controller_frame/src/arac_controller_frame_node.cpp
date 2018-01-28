#include <ros/ros.h>
#include <iostream>

#include "arac_controller_frame/aracControllerFrame.hpp"


int main(int argc, char **argv)
{
  arac_controller_frame::aracControllerFrame controllerFrame = arac_controller_frame::aracControllerFrame();
  controllerFrame.init(argc,argv);
  return controllerFrame.execute();
}
