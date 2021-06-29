#pragma once

#include <string>
#include <ros/ros.h>
#include <std_msgs/Int64.h>
#include <dependency_injection_ros/di_calculator.h>

class RosMiddleware : public Calculator::MiddlewareHandle {
 public:
  RosMiddleware(const ros::NodeHandle& nh,
                const std::string& in_topic,
                const std::string& out_topic)
  : nh_{nh},
    in_topic_{in_topic},
    pub_{nh_.advertise<std_msgs::Int64>(out_topic, 10))
  {}

  void registerCallback(Callback cb) override {
    sub_ = nh_.subscribe(in_topic_, 10, cb);
  }

  void publish(std_msgs::Int64 msg) override {
    pub_.publish(msg);
  }

 private:
   ros::NodeHandle nh_;
   std::string in_topic_;
   ros::Subscriber sub_;
   ros::Publisher pub_;
};
