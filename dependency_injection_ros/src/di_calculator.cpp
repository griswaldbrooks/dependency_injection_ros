#include <memory>
#include <utility>

#include <std_msgs/Int64.h>

#include "dependency_injection_ros/di_calculator.h"

Calculator::Calculator(std::unique_ptr<MiddlewareHandle> mw)
: mw_{std::move(mw)} {
  mw_->registerCallback([this](const std_msgs::Int64::ConstPtr& msg){
    std_msgs::Int64 incremented;
    incremented.data = msg->data + 1;
    mw_->publish(incremented);
  });
}
