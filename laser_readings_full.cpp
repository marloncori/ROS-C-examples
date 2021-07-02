#include <ros/ros.h>
#include <rosobot_control/rosbot_class.h>    
    
int main(int argc, char** argv){
    ros::init(argc, argv, "robot_node");
   	
   	RosbotClass rosbot;
   	
	rosbot.move_forward();
	
	//get readings
   	float right = rosbot.get_laser(121);
   	float left = rosbot.get_laser(431);
   	
   	//define and assign array values
   	float array_laser[] = [left, right];
   	ROS_INFO_STREAM("the wall is at " << array_laser[0] << "meters to the left and at " << array_laser[1] << "meters to the right.");
   	
	
	return 0;
}
