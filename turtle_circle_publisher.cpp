#include "ros/ros.h"
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_circle_publisher");
    ros::NodeHandle nh;

    ros::Publisher turtle_circle_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);

    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        geometry_msgs::Twist turtle_circle_msg;

        turtle_circle_msg.linear.x = 0.6;
        turtle_circle_msg.angular.z = 0.3;

        turtle_circle_pub.publish(turtle_circle_msg);
        ROS_INFO_STREAM("linear.x " << turtle_circle_msg.linear.x << "angular.z " << turtle_circle_msg.angular.z);
        ros::spinOnce();


        loop_rate.sleep();
    }

    return 0;
}
