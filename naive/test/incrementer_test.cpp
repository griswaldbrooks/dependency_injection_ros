// C++ Standard Library
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

// Boost
#include <boost/make_shared.hpp>

// Gtest
#include <gtest/gtest.h>

// ROS
#include <std_msgs/Int64.h>
#include <ros/ros.h>

// Code being tested
#include <naive/incrementer.h>

using namespace std::chrono_literals;

class Spinner {
 public:
   Spinner() :spin{[this]{
     while (!done && ros::ok()) {
       ros::spinOnce();
       ros::Duration(0.01).sleep();
     }
   }}{}

   ~Spinner() {
     done = true;
     spin.join();
   }
 private:
   std::atomic<bool> done{false};
   std::thread spin;
};

TEST(CalculatorTests, RegisterSubscriber) {
  ros::NodeHandle nh;
  Incrementer incrementer{nh, "/in", "/out"};

  std_msgs::Int64::Ptr result;
  ros::Subscriber sub = nh.subscribe<std_msgs::Int64>("/out", 0, [&](const auto& msg){
    result = boost::make_shared<std_msgs::Int64>(*msg);
  });
  EXPECT_EQ(sub.getNumPublishers(), 1);

  std_msgs::Int64 msg;
  msg.data = 7;
  ros::Publisher pub = nh.advertise<std_msgs::Int64>("/in", 0);
  EXPECT_EQ(pub.getNumSubscribers(), 1);
  pub.publish(msg);

  {
    size_t i = 0;
    while (ros::ok() && result == nullptr && i < 100) {
      ros::spinOnce();
      ros::Duration(0.01).sleep();
      ++i;
    }

    if (i == 100) FAIL();
    if (!ros::ok()) FAIL();
  }
  EXPECT_EQ(result->data, 8);
}

TEST(CalculatorTests, RegisterSubscriberSpinner) {
  ros::NodeHandle nh;
  Spinner spin;
  Incrementer incrementer{nh, "/in", "/out"};
  std::condition_variable cv;
  std::mutex m;
  std_msgs::Int64::Ptr result;
  ros::Subscriber sub = nh.subscribe<std_msgs::Int64>("/out", 0, [&](const auto& msg){
    result = boost::make_shared<std_msgs::Int64>(*msg);
    cv.notify_one();
  });
  EXPECT_EQ(sub.getNumPublishers(), 1);

  std_msgs::Int64 msg;
  msg.data = 7;
  ros::Publisher pub = nh.advertise<std_msgs::Int64>("/in", 0);
  EXPECT_EQ(pub.getNumSubscribers(), 1);
  pub.publish(msg);
  std::unique_lock<std::mutex> lock{m};
  cv.wait_for(lock, 10s, [&]{return result != nullptr;});

  EXPECT_EQ(result->data, 8);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "naive_test");
    ros::NodeHandle nh;
    return RUN_ALL_TESTS();
}
