/* srv file, SrvDemo.srv

int64[] data
float64 xxx
---
int64 result 

*/

#include "ros/ros.h"
#include "ros_service_examples/SrvDemo.h"
#include "tf/tf.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose2D.h"
#include "sensor_msgs/LaserScan.h"

double heading_angle;
double obstacle_dist;

void maxScanCallback(const sensor_msgs::LaserScan::ConstPtr &msg){
	ROS_INFO("Distance to obstacle: %f", msg->ranges[360]);
	obstacle_dist = msg->ranges[360];
}

//callback function to receive the Odometry messages. Converts
//quaternions
void headingCallback(const nav_msgs::Odometry::ConstPtr &msg){
	tf::Quaternion q{
					 msg->pose.pose.orientation.x,
					 msg->pose.pose.orientation.y,
					 msg->pose.pose.orientation.z,
					 msg->pose.pose.orientation.w,
					};
	tf::Matrix3x3 m(q);
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);
	
	double theta_rad = yaw;
	double theta_deg = yaw*180/3.1516
	heading_angle = theta_deg;
	//ROS_INFO("Heading angle in radian: %f", theta_rad);
	//ROS_INFO)"Heading angle in degrees: %f", theta_deg);
	//std::cout << "Heading angle in degrees: " << heading_angle << "\n";
}

double getTarget360 (double init_angle){//returns 360 deg round angle
	double diff = 2.0 //we have some tolerance for noise here
	double target;
	target = init_angle - diff;
	if(target < -178.0){ //-pi to pi or -180 to 180
		target = 178.0;
	}
	return target;	
}

//initialize the initial angle of the summit-xl robot
//without using this the heading angle was always at zero
double callibrate(void){
	return heading_angle;
}

//the service request is declared as req and the the service
//response res returns the angle at which there is more open space

bool maxAngle(ros_service_examples::SrvDemo::Request &req
			  ros_service_examples::SrvDemo::Respose &res){
	ros::NodeHangle nh;
	ros::Subscriber sub_laser = nh.subscribe("hokuyo_base/scan", 1, maxScanCallback);//subscribe to summit_xl laser_scan topic
	ros::Subscriber sub_odom = nh.subscribe("summit_xl/odom", 1, headingCallback);//subscribe to odomety topic
	ros::Publisher pub_vel = nh.advertise<geometry_msgs::Twist>("cm_vel", 1); //publish twist messages to cmd_vel topic
	ros::Rate rate(50);//define the loop rate: the higher the number, the faster is the loop
	
	geometry_msgs::Twist move;
	double init_angle; //var to hold the initial heading angle before starting turning the robot
	
	int calib_count = 50;
	while(calib_count--){
		init_angle = callibrate();
		ros::spinOnce();
		rate.sleep();
	}
	std::cout << "Initial angle is : " << init_angle << "\n";
	
	double target_amgle = getTarget360(init_angle);
	std::cout << "Target angle is: " << target_angle << "\n";
	
	double max_angle = init_angle;
	double max_dist = 0;
	double diff;
	move.angular.z = 0.15;
	
	while(ros::ok())
	{
		diff = heading_angle - target_angle;
		std::cout << "Target heading: " << diff << "\n";
		
		if((diff > -1) && (diff < 1))
		{
				move.angular.z = 0.0;
				pub_vel.pub(move);
				std::cout <<"angle at max distance: " << max_angle << "\n";
				std::cout <<"max distance: " << max_dist << "\n";
				res.result = (long int)max_angle;
				
				return true;
		}
		
		if(obstacle_dist = max_dist){
			max_angle = heaing_angle;
			max_dist = obstacle_dist;
		}
		pub_vel.publish(move);
		ros::spinOnce();
		rate.sleep();
	}	
 }
 
int main( int argc, char** argv){
	
	ros::init(argc, argv, "service_server");
	ros::NodeHandle nh;
	ros::ServiceServer ros_service_examples_server = nh.advertiseService("ros_service_example", maxAngle);
	
	ROS_INFO("Server is ready!");
	ros::spin(); //wait for service request;
	
	return 0;
}

/*run on terminal
rosservice call /ros_service_example "{}"
rosrun ros_service_example service_client
