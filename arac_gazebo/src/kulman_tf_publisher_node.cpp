#include <ros/ros.h>
#include <iostream>

#include "arac_gazebo/KulmanTfPublisher.hpp"


int main(int argc, char **argv)
{
  kuco::KulmanTfPublisher kulmanTfPublisher = kuco::KulmanTfPublisher();
  kulmanTfPublisher.execute();
  return 0;
}
