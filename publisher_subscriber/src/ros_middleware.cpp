#include <string>
#include <ros/ros.h>
#include <std_msgs/Int64.h>
#include <publisher_subscriber/ros_middleware.h>


RosMiddleware::RosMiddleware(const ros::NodeHandle& nh,
                const std::string& in_topic,
                const std::string& out_topic)
  : nh_{nh},
    in_topic_{in_topic},
    pub_{nh_.advertise<std_msgs::Int64>(out_topic, 10)}
  {}

  void RosMiddleware::registerCallback(Callback cb) {
    sub_ = nh_.subscribe<std_msgs::Int64>(in_topic_, 10, cb);
  }

  void RosMiddleware::publish(std_msgs::Int64 msg) {
    pub_.publish(msg);
  }
