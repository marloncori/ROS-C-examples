/* add to CMakeLists.txt

add_executable(robot_commander src/robot_commander.cpp)
add_dependencies(robot_commander S{robot_commander_EXPORTED_TARGETS} S(catkin_
target_link_libraries(robot_commander S{catkin_LIBRARIES}) */

#include <geomtry_msgs/Twist.h>
#include <ros/ros.h>
using namespace std;

class MyRobot{
	private:
		string robot_name;
		ros::NodeHandle n_;
		ros::Publisher speed_pub_;
	
	public:
		MyRobot(ros::NodeHandle& nh, string robot_model): n_(nh){		
			robot_name_ = robot_model;
			speed_pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
		}
		
		void speed(){
			geometry_mgsg::Twist vel;
			
			vel.linear.x = 0.2;
			vel.angular.z = 0.2;
			speed_pub_.publish(vel);	
		}
};

int main( int argc, char **argv){
	
	ros::init(argv, argv, "my_node");
	ros::NodeHandle nh;
	
	MyRobot MP0700(nh, "Neobotix MPO 700");
	
	ros::Rate loop_rate(10);
	while(ros::ok()){
		MPO700.speed();
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
