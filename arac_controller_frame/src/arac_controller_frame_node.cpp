#include <ros/ros.h>
#include <iostream>

#include "arac_controller_frame/AracControllerFrame.hpp"


int main(int argc, char **argv)
{
  kuco::AracControllerFrame controllerFrame = kuco::AracControllerFrame();
  controllerFrame.create();
  controllerFrame.initilize(argc,argv);
  controllerFrame.execute();
  return 0;
}
