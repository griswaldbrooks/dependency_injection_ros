#include <memory>
#include <utility>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <dependency_injection_ros/di_calculator.h>

struct MockMiddleware : public Calculator::MiddlewareHandle {
  MOCK_METHOD(void, registerCallback, (Callback cb), (override));
  MOCK_METHOD(void, publish, (std_msgs::Int64 msg), (override));
};

TEST(SuiteName, TestName) {
  auto mw = std::make_unique<MockMiddleware>;

  Calculator::MiddlewareHandle::Callback callback;
  EXPECT_CALL(*mw, registerCallback(_)).WillOnce(
    Invoke([&](Calculator::MiddlewareHandle::Cb cb) { callback = cb;}));

  std_msgs::Int64 expected;
  expected.data = 8;
  EXPECT_CALL(*mw, publish(expected)).Times(1);

  Calculator calc{std::move(mw)};

  std_msgs::Int64 msg;
  msg.data = 7;
callback(msg);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
