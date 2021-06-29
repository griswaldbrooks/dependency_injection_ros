#include <memory>

#include <ros/ros.h>

#include "dependency_injection_ros/ros_middleware.h"
#include "dependency_injection_ros/di_calculator.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Calculator");
  ros::NodeHandle n;
  Calculator calculator{std::make_unique<RosMiddleware>(n, "/in", "/out")};

  ros::spin();

  return 0;
}
