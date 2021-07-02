#include "ros/ros.h"
#include "ros_service_examples/Person.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "own_service_client");
	ros::NodeHandle nh;
	
	ros::service::waitForService("/show_person");
	ros::ServiceClient person_client = nh.serviceClient<ros_service_examples::Person>("/show_person");
	
	ros_service_examples::Person person_srv;
	person_srv.request.name = "Marlon";
	person_srv.request.age = 35;
	person_srv.request.gender = "male";
	
	ROS_INFO_STREAM("service client to show person infos, name: " << person_srv.request.name << " age: " << (int)person_srv.request.age
                    << " gender: " << person_srv.request.gender);
    
    person_client.call(person_srv);
    ROS_INFO_STREAM("show person result: " << person_srv.response);
    
	return 0;
}
