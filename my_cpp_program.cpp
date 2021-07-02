#include <ros/ros.h>
#include "my_cpp_package/PID.h"

std::string printerMethod(std::string);

int main( int argc, char** argv){
	ros::init(argc, argv, "my_node");
	ros::NodeHandle nh;
	
	std::string result2 = printerMethod("the humanoid robot");
	std::cout << result2;
	
	return 0;
}

std::string printerMethod(std::string robot_name){
	std::cout << "Hi, ROS developer, what is your robot name?";
	std::string robot;
	std::cin >> robot;
	
	std::string text = "Keep pushing your ROS learning!\n";
	std::string string_result = robot + " " + robot_name + text;
	
	strcpy(result, string_result.c_str());
	
	return string_result;
}

