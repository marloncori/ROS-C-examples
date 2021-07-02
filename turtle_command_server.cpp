#include "ros/ros.h"
#include "std_srvs/Trigger.h"
#include "geometry_msgs/Twist.h"
using namespace ros;

bool pubCommand = false;

bool commandCallback(std_srvs::Trigger::Request &req
                    std_srvs::Trigger::Response &res)
{
	pubCommand = !pubCommand;
	ROS_INFO("Publish turtle velocity command [%s]", pubCommand==true"Yes":"No");
	res.success = True;
	res.message = "Change turtle command state!";
	return true;	
	
}
int main(int argc, char ** argv){
	
	init(argc, argv, "turtle_command_server");
	NodeHandle nh;
	ServiceServer command_server = nh.advertiseService("/turtle_command", commandCallback);
	Publisher turtle_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
	ROS_INFO("Ready to receive turtle command.");
	
	Rate loop_rate(10);
	
	while(ok()){
		spinOnce();
		
		if(pubCommand){
			geometry_msgs::Twist vel_msg;
			vel_msg.linear.x = 0.5;
			vel_msg.angular.z = 0.2;
			turtle_vel_pub.publish(vel_msg);
		}
		loop_rate.sleep();
	}	
	
	return 0;
}
