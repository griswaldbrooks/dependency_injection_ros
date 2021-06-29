cmake_minimum_required(VERSION 2.8.3)
project(dependency_injection_ros)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs genmsg)

message("TACOS")
message(${PROJECT_SOURCE_DIR})

## Declare a catkin package
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS
    std_msgs
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(calculator src/calculator.cpp)
target_link_libraries(calculator ${catkin_LIBRARIES})

add_executable(di_calculator src/di_calculator.cpp)
target_link_libraries(di_calculator ${catkin_LIBRARIES})
# add_dependencies(calculator beginner_tutorials_generate_messages_cpp)
