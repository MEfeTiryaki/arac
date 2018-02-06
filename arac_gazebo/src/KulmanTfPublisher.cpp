// arac gazebo
#include "arac_gazebo/KulmanTfPublisher.hpp"

namespace KulmanTfPublisher {

// Note : param_io is needed to use the getParam
using namespace param_io;
KulmanTfPublisher::KulmanTfPublisher()
{
}

KulmanTfPublisher::~KulmanTfPublisher()
{
}

kulmanTfPublisher::init(){
  ros::init(argc, argv, nodeName_);

  nodeHandle_ = new ros::NodeHandle("~");

  robotStateSubscriber_ = nodeHandle_->subscribe(topicName, 10,
                    &aracControllerFrame::robotStateCallback, this);

  loop_rate_= new ros::Rate(400);
}

KulmanTfPublisher::execute()
{
  while (ros::ok()) {

    const auto& pose  = model_->GetLink(frameBase_)->GetWorldPose();
    // Odom
    odomTransform.setOrigin( tf::Vector3(pose.pos.x,pose.pos.y,pose.pos.z ));
    odomTransform.setRotation(tf::Quaternion(pose.rot.x,pose.rot.y,pose.rot.z,pose.rot.w));

    static tf::TransformBroadcaster br;
    br.sendTransform(tf::StampedTransform(odomTransform, ros::Time::now(), frameWorld_ , frameBase_));


    ros::spinOnce();
    loop_rate_->sleep();
  }
}

KulmanTfPublisher::robotStateCallback(arac_msgs::AracState msg){

}

} /* namespace arac_controller_frame*/
