# dependency_injection_ros
Basic ROS1 example on doing dependency injection

# Things that need to be organized into something coherent
- Pure virtual handle interfaces
  - Stylistic choice, makes interfaces portable
  - Removes dependence (specifically when writing mocks) on constructor details for the ROS handle
