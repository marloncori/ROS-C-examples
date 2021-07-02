#include "ros/ros.h"
#include "ros_service_examples/SrvDemo.h"

int main( int argc, char** argv){
	
	ros::init(argc, argv, "service_client");
	ros::NodeHandle nh;
	
	ros::ServiceClient ros_service_examples_client = nh.serviceClient<ros_service_examples::SrvDemo>("ros_service_example");
	ros_service_example::SrDemo srv;
	
	if(ros_service_example_client.call(srv)){
		ROS_INFO("Receive srv, srv.Response.result = Angle at max open space: %ld", (long int)srv.response.result);
	}else{
		ROS_ERROR("Failed to call servie: ros_service_example");
		return 1;
	}
	
	return 0;
}
/*change CMakeLists.txt file
add_executable(service_server src/service_server.cpp)
add_dependencies(service_server S{S{PROJECT_NAME}_EXPORT_TARGETS} S{catkin_EXPORTED_TARGETS})
target_link_libraries(service_server S{catkin_LIBRARIES})

add_executable(service_client src/service_client.cpp)
add_dependencies(service_client S{S{PROJECT_NAME}_EXPORT_TARGETS} S{catkin_EXPORTED_TARGETS})
target_link_libraries(service_client S{catkin_LIBRARIES})

modify also package.xml */
