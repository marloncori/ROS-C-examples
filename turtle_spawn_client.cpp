#include <ros/ros.h>
#include "turtlesim/Spawn.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "turtle_spawn_client");
	ros::NodeHandle n;
	
	ros::service::waitForService("/spawn");
	ros::ServiceClient turtle_spawn_cli = n.serviceClient<turtlesim::Spawn>("/spawn");
	
	turtlesim::Spawn srv;
	srv.request.x = 2.0;
	srv.request.y = 2.0;
	srv.request.name = "second_turtle";
	
	turtle_spawn_cli.call(srv);
	ROS_INFO("spawn the second turtle, location: %d, %d, name: %s", srv.request.x, srv.request.y, srv.request.name.c_str());
	
	return 0;
}
