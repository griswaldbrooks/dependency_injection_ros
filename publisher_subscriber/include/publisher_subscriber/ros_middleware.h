#pragma once

#include <string>
#include <ros/ros.h>
#include <publisher_subscriber/incrementer.h>

class RosMiddleware : public Incrementer::MiddlewareHandle {
 public:
  RosMiddleware(const ros::NodeHandle& nh,
                const std::string& in_topic,
                const std::string& out_topic);
  void registerCallback(Callback cb) override;
  void publish(std_msgs::Int64 msg) override;

 private:
   ros::NodeHandle nh_;
   std::string in_topic_;
   ros::Subscriber sub_;
   ros::Publisher pub_;
};
