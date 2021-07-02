/* 
    Person.srv

string name
uint8  age
string gender

---
string result 

*/
#include<ros/ros.h>
#include "ros_service_examples/Person.h"

bool personCallback(ros_service_examples::Person::Request &req, 
                    ros_service_examples::Person::Response &res)
{
	ROS_INFO_STREAM("/n/tPerson: name: " << req.name << " age: " << (int)req.age << " gender: " << req.gender);
    res.result = "ok";
    
    return true;
}
                    	
int main(int argv, char **argc){
	
	ros::init(argv, argc, "own_service_server");
	ros::NodeHandle nh;
	
	ros::ServiceServer person_service = nh.advertiseService("/show_person", personCallback);
	
	ROS_INFO("Ready to show person information.");
	ros::spin();
	
	
	return 0;
}
