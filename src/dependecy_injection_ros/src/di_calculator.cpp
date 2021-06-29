#include <functional>
#include <memory>

#include <ros/ros.h>
#include <std_msgs/Int64.h>

class Calculator
{
 public:
  struct MiddlewareHandle {
    using Callback = std::function<void(const std_msgs::Int64::ConstPtr&)>;
    virtual void registerCallback(Callback cb) = 0;
    virtual void publish(std_msgs::Int64 msg) = 0;
    virtual ros::Time now() = 0;
    virtual ~MiddlewareHandle();
  };

  Calculator(std::unique_ptr<MiddlewareHandle> mw) : mw_{std::move(mw)}{
    mw_->registerCallback(doit);
  }

  void doit(const std_msgs::Int64::ConstPtr& msg, Mock m) {
    std_msgs::Int64 incremented = msg;
    incremented.data += 100;
    if (condition) {
      incremented.data -= 99;
    }
    else {
      incremented.data = 1;
    }
    mw_->publish(incremented);
  }
 private:
   std::unique_ptr<MiddlewareHandle> mw_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Calculator");
  ros::NodeHandle n;
  Calculator calculator(std::make_unique<RosMiddleware>(n, "/in", "/out"));

  ros::spin();

  return 0;
}
