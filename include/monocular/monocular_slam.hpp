#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>

#include "System.h"
#include "Frame.h"
#include "Map.h"
#include "Tracking.h"

namespace monocular {

class SlamNode: public rclcpp::Node {
public:
  SlamNode(ORB_SLAM3::System*);
  ~SlamNode();

private:
  ORB_SLAM3::System* slam_obj;
  cv_bridge::CvImagePtr cv_ptr;
  sensor_msgs::msg::Image front_image;

private:

  bool got_front_image;

  rclcpp::TimerBase::SharedPtr maintimer;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub;

private:
  void mainloop();
  void monocular_image_callback(const sensor_msgs::msg::Image::SharedPtr);
};

};

