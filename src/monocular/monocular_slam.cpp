#include <chrono>
#include "monocular/monocular_slam.hpp"
#include "orb/utility.hpp"

using namespace monocular;
using std::placeholders::_1;

SlamNode::SlamNode(ORB_SLAM3::System* slam_obj): Node("monocular_vslam_node") {
  this->slam_obj = slam_obj;
  this->got_front_image = false;
  this->maintimer = this->create_wall_timer(
    std::chrono::milliseconds(10),
    std::bind(&SlamNode::mainloop, this));
  this->image_sub = this->create_subscription<sensor_msgs::msg::Image>(
    "/front/camera_raw", 1, 
    std::bind(&SlamNode::monocular_image_callback, this, std::placeholders::_1));  
}

SlamNode::~SlamNode() {
  this->slam_obj->Shutdown();
}

void SlamNode::monocular_image_callback(const sensor_msgs::msg::Image::SharedPtr img_ptr) {
  this->front_image = *img_ptr;
  try {
    this->cv_ptr = cv_bridge::toCvCopy(img_ptr);
  }catch (cv_bridge::Exception& e) {
    std::cerr << "cv_bridge error: " << e.what() << std::endl;
    return ;
  }
 

  this->got_front_image = true;
}

void SlamNode::mainloop() {
  if (!this->got_front_image) {
    std::cerr << "No image recieved" << std::endl;
    return ;
  }
  this->slam_obj->TrackMonocular(this->cv_ptr->image, 
    utility::stamp_to_sec(this->front_image.header.stamp));
}
