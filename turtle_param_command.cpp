#include <ros/ros.h>
#include "std_srvs/Empty.h"
using namespace ros;

int main(int argc, char **argv)
{
	int red, green, blue;
	
	init(argc, argv, "turtle_param_command");
	NodeHandle nh;
	
	param::get("/background_r", red);
	param::get("/background_g" green);
	param::get("/background_b", blue);
	
	ROS_INFO_STREAM("get background color " << red << " " << green << " " << blue);
	
	param::set("/background_r", 255);
	param::set("/background_g", 255);
	param::set("/background_b", 255);
	
	ROS_INFO_STREAM("set background color white");
	
	param::get("/background_r", red);
	param::get("/background_g" green);
	param::get("/background_b", blue);
	
	ROS_INFO_STREAM("the background color now is " << red << " " << green << " " << blue);
	
	//call the service and refresh background color
	service::waitForService("/clear");
	ServiceClient clear_background = nh.serviceClient<std_srvs::Empty>("/clear");
	
	std_srvs::Empty srv;
	clear_background.call(srv);
	
	sleep(1);
	
	
	return 0;
}
