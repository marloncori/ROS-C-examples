#include <sensor_msgs/LaserScan.h>
#include <ros/ros.h>

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr &scan){
	
	int size = scan->ranges.size();
	int middle = size / 2;
	float range = scan->ranges[middle];
	
	ROS_INFO("RANGE[%d]=%f", middle, range);
}

int main(int argc, char** argv){
	
	ros::init(argc, argv, "my_node");
	ros::NodeHandle nh;
	
	ros::Subscriber sub = nh.subscribe("/sick_300_front/scan", 1, chatterCallback);
	ros::spin();
	
	return 0;
}
