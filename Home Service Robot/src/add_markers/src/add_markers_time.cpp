#include <ros/ros.h>
#include <visualization_msgs/Marker.h>


using namespace std;


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  while (ros::ok()){
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

    marker.lifetime = ros::Duration(5);
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1) {
  	if (!ros::ok()) {
    	return 0;
  	}
  	ROS_WARN_ONCE("Please create a subscriber to the marker");
  	sleep(1);
    }
    marker.pose.position.x = -1.5;
    marker.pose.position.y = -3;
    marker_pub.publish(marker);
    ROS_INFO("Showing the pick up location");
    ros::Duration(5).sleep();
    ROS_INFO("Hiding the pick up location");
    ros::Duration(5).sleep();

    marker.pose.position.x = -1.8;
    marker.pose.position.y = -1.8;
    marker_pub.publish(marker);
    ROS_INFO("Showing the drop off location");
    ros::Duration(5).sleep();
    ROS_INFO("Hiding the drop off location");
    ros::Duration(5).sleep();

  }
  r.sleep();
  //return 0;
}


