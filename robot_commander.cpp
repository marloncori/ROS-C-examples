/* add to CMakeLists.txt

add_executable(robot_commander src/robot_commander.cpp)
add_dependencies(robot_commander S{robot_commander_EXPORTED_TARGETS} S(catkin_
target_link_libraries(robot_commander S{catkin_LIBRARIES}) */

#include <geomtry_msgs/Twist.h>
#include <ros/ros.h>
#include <ctime>
#include <random>

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
		
		float get_speed(){
		   bool first = false;
		   if(!first){
		     srand (static_cast <unsigned> (time(0)));
		     first = true;
		   }
	         return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
	
		void set_speed(){
			geometry_mgsg::Twist vel;
			float linear_speed = get_speed();
			float angular_speed = get_speed();
			
			vel.linear.x = linear_speed;
			vel.angular.z = angular_speed;
			cout << "\n==========================================================" << endl;
			ROS_INFO("\tThis is the current speed of %s:\n", robot_name_);
			speed_pub_.publish(vel);
			cout << "==========================================================" << endl;
		}
};

int main( int argc, char **argv){
	
	ros::init(argv, argv, "my_node");
	ros::NodeHandle nh;
	
	MyRobot MP0700(nh, "Neobotix MPO 700");
	
	ros::Rate loop_rate(10);
	while(ros::ok()){
		MPO700.set_speed();
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
