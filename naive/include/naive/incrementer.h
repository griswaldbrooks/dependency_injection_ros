#pragma once

#include <string>

#include <ros/ros.h>

class Incrementer
{
 public:
  Incrementer(ros::NodeHandle& nh,
              const std::string& in_topic,
              const std::string& out_topic);

 private:
   ros::Publisher pub_;
   ros::Subscriber sub_;
};
