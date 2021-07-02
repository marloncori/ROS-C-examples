#include <ros/ros.h>
#include <rosobot_control/rosbot_class.h>    
    
int main(int argc, char** argv){
    ros::init(argc, argv, "robot_node");
   	
   	RosbotClass rosbot;
   	rosbot.move_forward(3);
   	
   	float *pointer;
   	
   	pointer = rosbot.get_laser_full();
   	ROS_INFO_STREAM("Laser values: ");
   	for(int i = ; i < 720; i++){
   		ROS_INFO_STREAM(*pointer);
   		pointer++;
	   }
	
	return 0;
}
