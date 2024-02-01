cmake_minimum_required(VERSION 3.8)
project(nav2_action_cancel)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(nav2_msgs REQUIRED)

# Define executable
add_executable(nav2_action_cancel src/nav2_action_cancel.cpp)
ament_target_dependencies(nav2_action_cancel
  rclcpp
  rclcpp_action
  nav2_msgs
)

# Install the executable
install(TARGETS
  nav2_action_cancel
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  # Skip linters as before
  set(ament_cmake_cpplint_FOUND TRUE)
  set(ament_cmake_copyright_FOUND TRUE)
endif()

ament_package()

