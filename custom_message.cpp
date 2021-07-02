/*custom.msg

std_msgs/String robot_name
std_msgs/String date_time
geomertry_msgs/Pose2D location
*/
#include "ros/ros.h"
#include "beginner_tutorials/custom.h"
#include<ctime>
#include<chrono>
#include<sstream>

int main(int argc, char **argv){
	
	ros::init(argc, argv, "talker");
	ros::NodeHandle nh;
	
	ros::Publisher pub = nh.advertise<beginner_tutorials::custom>("custom_msg", 10);
	ros::Rate loop_rate(10);
	
	while(ros::ok()){
		
		beginner_tutorials::custom msg;
		msg.robot_name_data = "RaspberryPi_Robot_1";
		
		auto end = std::chrono::system_clock::now();
		std::time_t endTime = std::chrono::system_clock::to_time_t(end);
		msg.date_time.data = std::ctime(&endTime);
		
		msg.location.x = 5;
		msg.location.y = 5;
		msg.location.theta = 90;
		
		pub.publish(msg);
		loop_rate.sleep();
	}	
	return 0;
}
