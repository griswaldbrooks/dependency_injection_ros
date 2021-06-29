#pragma once

#include <functional>
#include <memory>

#include <std_msgs/Int64.h>

class Calculator
{
 public:
  struct MiddlewareHandle {
    using Callback = std::function<void(const std_msgs::Int64::ConstPtr&)>;
    virtual void registerCallback(Callback cb) = 0;
    virtual void publish(std_msgs::Int64 msg) = 0;
    virtual ~MiddlewareHandle() = default;
  };

  Calculator(std::unique_ptr<MiddlewareHandle> mw);

 private:
   std::unique_ptr<MiddlewareHandle> mw_;
};
