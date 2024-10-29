#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <cmath>

using namespace std;

double robot_x, robot_y;

void odom_callback(const nav_msgs::Odometry &msg)
{
  robot_x = msg.pose.pose.position.x;
  robot_y = msg.pose.pose.position.y;
}

//This function aims to calculate the distance between the robot and marker
double dis_target(double x1, double y1, double x2, double y2)
{
  double dis = sqrt( pow((x1-x2),2) + pow((y1-y2),2));
  //cout << "robot x" << x1 << "robot y"<< y1 << endl;
  //cout << "marker x" << x2 << "maker y"<< y2 << endl;
  //cout << dis << endl;
  //sleep(3);
  return dis;
}


//This function aims to detect if robot arrives the target
bool is_arrived(double x1, double y1, double x2, double y2)
{
  return dis_target(x1, y1, x2, y2) < 0.15;
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber marker_sub = n.subscribe("odom", 10, odom_callback);

  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "add_markers";
  marker.id = 0;
  uint32_t shape = visualization_msgs::Marker::CUBE;
  marker.type = shape;
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = -1.5;
  marker.pose.position.y = -3;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 0.5;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.3;
  marker.scale.y = 0.3;
  marker.scale.z = 0.05;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 0.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();
  marker_pub.publish(marker);


  bool is_picked_up = false;
  bool is_off = false;
  bool control = false;

  marker_pub.publish(marker);
  ROS_INFO("Sending pick-up goal");

  while (ros::ok())
  {
    ros::spinOnce();
      //this is because the amcl frame and world frame doesn't match
      is_picked_up = is_arrived(robot_y,-robot_x, marker.pose.position.x, marker.pose.position.y); 
      is_off = is_arrived(robot_y,-robot_x, -1.8, -1.8);
      //cout << "Pick_up Condition" << is_picked_up << endl;
      //cout << "Control Condition" << control << endl;
      //cout << "Drop_off Condition" << is_off << endl;

      if (is_picked_up){
	if (!control){
	  ROS_INFO("The Item is Picked up!");
	  marker.action = visualization_msgs::Marker::DELETE;
	  marker_pub.publish(marker);
	  // Change the pose of the marker
	  //marker.action = visualization_msgs::Marker::ADD;
	  marker.pose.position.x = -1.8;
	  marker.pose.position.y = -1.8;
	  marker.action = visualization_msgs::Marker::ADD;
	  ros::Duration(5).sleep();
	  //marker_pub.publish(marker);
	  ROS_INFO("Robot is driving to the drop-off point!");
	  control = true;
	}
      }

      if (is_off){
        ROS_INFO("The Item is Dropped Off!");
	marker_pub.publish(marker);
	ros::Duration(5).sleep();
      }
      else {
	if (!control){
          marker_pub.publish(marker);
	}
      }
  }
  r.sleep();
  //return 0;
}


