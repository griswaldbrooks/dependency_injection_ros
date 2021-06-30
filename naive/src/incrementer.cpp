#include <ros/ros.h>
#include <std_msgs/Int64.h>

#include "naive/incrementer.h"

Incrementer::Incrementer(ros::NodeHandle& nh,
                         const std::string& in_topic,
                         const std::string& out_topic)
  : pub_{nh.advertise<std_msgs::Int64>(out_topic, 10)},
    sub_{nh.subscribe<std_msgs::Int64>(in_topic, 10, [this](const auto& msg) {
      std_msgs::Int64 incremented;
      incremented.data = msg->data + 1;
      pub_.publish(incremented);
    })}
  {}