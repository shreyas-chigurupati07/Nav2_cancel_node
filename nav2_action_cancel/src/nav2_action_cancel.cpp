#include <memory>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp/time.hpp"

#include "nav2_msgs/action/navigate_to_pose.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class Nav2ActionCancel : public rclcpp::Node
{
public:
  using NavigateToPose = nav2_msgs::action::NavigateToPose;
  //using GoalHandleNavigateToPose = rclcpp_action::ClientGoalHandle<NavigateToPose>;
  rclcpp_action::Client<NavigateToPose>::SharedPtr client_ptr_;

  explicit Nav2ActionCancel(): Node("nav2_send_goal")
  {
    this->client_ptr_  = rclcpp_action::create_client<NavigateToPose>(this, "navigate_to_pose");
  }

  void cancelGoals()
  {
    if (!this->client_ptr_->wait_for_action_server())
    {
      RCLCPP_INFO(get_logger(), "Action server unavailable");
      return;
    }
    auto cancel_future = client_ptr_->async_cancel_all_goals();
    auto cancel_result = cancel_future.wait_for(std::chrono::seconds(1));

    if (cancel_result == std::future_status::ready || cancel_result == std::future_status::timeout)
    {
      RCLCPP_INFO(get_logger(), "Action was cancelled successfully");
    }
    else
    {
      RCLCPP_INFO(get_logger(), "Action cancellation failed");
    }
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto nav2_cancel_node = std::make_shared<Nav2ActionCancel>();
  nav2_cancel_node->cancelGoals();
  //rclcpp::spin(nav2_cancel_node);
  rclcpp::spin(nav2_cancel_node);
  //rclcpp::spin_some(node->get_node_base_interface());
  rclcpp::shutdown();
  return 0;
}