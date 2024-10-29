#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
 
// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  

  //*************** Pick up **************//

  // Define a position and orientation for pick-up position
  goal.target_pose.pose.position.x = -1.5;
  goal.target_pose.pose.position.y = -3;
  goal.target_pose.pose.orientation.w = 0.5;


  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick-up goal");
  ros::Duration(5).sleep();
  ac.sendGoal(goal);
  
  // Wait an infinite time for the results
  ac.waitForResult();
  
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the robot moved to pick-up position");
    ros::Duration(5).sleep();}
  else{
    ROS_INFO("The robot failed to move to pick-up position for some reason");}

  //*************** Drop off **************//
  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  // Define a position and orientation for drop-off position
  goal.target_pose.pose.position.x = -1.8;
  goal.target_pose.pose.position.y = -1.8;
  goal.target_pose.pose.orientation.w = 1.0;


  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop-off goal");
  ac.sendGoal(goal);
  //ros::Duration(60).sleep();
  // Wait an infinite time for the results
  ac.waitForResult();
  //ros::Duration(60).sleep();
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the robot moved to drop-off position");
  else
    ROS_INFO("The robot failed to move to drop-off position for some reason");


  ros::Duration(60).sleep();
  return 0;
}



