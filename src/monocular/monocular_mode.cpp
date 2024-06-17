#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "monocular/monocular_slam.hpp"

#include "System.h"

int main(int argc, char **argv) {

  std::string path_to_vocabulary = "src/ORB_SLAM3_ROS2/vocabulary/ORBvoc.txt";
  std::string path_to_config = "src/ORB_SLAM3_ROS2/config/monocular/TUM1.yaml";

  rclcpp::init(argc, argv);
  ORB_SLAM3::System slam_obj(path_to_vocabulary, 
      path_to_config, 
      ORB_SLAM3::System::MONOCULAR, 
      true);

  auto node = std::make_shared<monocular::SlamNode>(&slam_obj);
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}

