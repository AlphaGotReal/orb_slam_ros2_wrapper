#include "rclcpp/rclcpp.hpp"
namespace utility {
  double stamp_to_sec(builtin_interfaces::msg::Time stamp) {
    return stamp.sec + (double)(stamp.nanosec) * 1e-9;
  }
};
