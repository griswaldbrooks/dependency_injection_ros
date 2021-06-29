#include <ros/ros.h>
#include <std_msgs/Int64.h>

class Calculator
{
 public:
  Calculator(const ros::NodeHandle& nh)
  : nh_{nh},
    sub_{nh_.subscribe("/in", 10, &Calculator::doit, this)},
    pub_{nh_.advertise<std_msgs::Int64>("/out", 10)}
  {}

  void doit(const std_msgs::Int64::ConstPtr& msg) {
    std_msgs::Int64 incremented = msg;
    incremented.data += 1;
    pub_->publish(incremented);
  }
 private:
   ros::NodeHandle nh_;
   ros::Subscriber sub_;
   ros::Publisher pub_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Calculator");
  ros::NodeHandle n;
  Calculator calculator(n);

  ros::spin();

  return 0;
}
