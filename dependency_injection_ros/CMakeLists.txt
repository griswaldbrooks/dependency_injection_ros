cmake_minimum_required(VERSION 2.8.3)
project(dependency_injection_ros)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs genmsg)

## Declare a catkin package
catkin_package(
  INCLUDE_DIRS
    include
  CATKIN_DEPENDS
    std_msgs
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_library(libdi_calculator
  src/di_calculator.cpp
  src/ros_middleware.cpp
)

target_link_libraries(libdi_calculator
  ${catkin_LIBRARIES}
)

add_executable(di_calculator
  src/di_node.cpp
)

target_link_libraries(di_calculator
  libdi_calculator
  ${catkin_LIBRARIES}
)

if (CATKIN_ENABLE_TESTING)
  catkin_add_gmock(di_calculator_tests test/di_calculator_test.cpp)
  target_link_libraries(di_calculator_tests
    libdi_calculator
    ${catkin_LIBRARIES}
  )
endif()

install(TARGETS di_calculator
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)
