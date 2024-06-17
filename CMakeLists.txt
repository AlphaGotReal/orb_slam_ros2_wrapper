cmake_minimum_required(VERSION 3.8)
project(orbslam3_wrapper)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(message_filters REQUIRED)
find_package(Sophus REQUIRED)
find_package(Pangolin REQUIRED)
find_package(ORB_SLAM3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
  include
  ${ORB_SLAM3_ROOT_DIR}/include
  ${ORB_SLAM3_ROOT_DIR}/include/CameraModels
)

link_directories(include)

# monocular mode
add_executable(monocular_mode 
  src/monocular/monocular_mode.cpp
  src/monocular/monocular_slam.cpp)
ament_target_dependencies(monocular_mode rclcpp sensor_msgs cv_bridge ORB_SLAM3 Pangolin OpenCV)

install(TARGETS 
  monocular_mode
  DESTINATION lib/${PROJECT_NAME})

ament_package()
