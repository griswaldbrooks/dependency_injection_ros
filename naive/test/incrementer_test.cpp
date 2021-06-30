// C++ Standard Library
#include <memory>

// Boost
#include <boost/make_shared.hpp>

// Gtest
#include <gtest/gtest.h>

// ROS
// #include <std_msgs/Int64.h>
#include <ros/ros.h>

// Code being tested
#include <naive/incrementer.h>

TEST(CalculatorTests, RegisterSubscriber) {
  SUCCEED();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "naive_test");
    ros::NodeHandle nh;
    return RUN_ALL_TESTS();
}
