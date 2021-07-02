/*
  Robot.msg
  
string name
uint8  DOF
string type
uint8 height
string weight

*/

#include "ros/ros.h"
#include "tutorials2/Robot.h"

void own_message_callback(const tutorials2::Robot::ConstPtr& own_msg)
{
    ROS_INFO("name: %s, DOF: %d, type: %s, height: %d, weight: %s", own_msg->name.c_str(), own_msg->DOF, own_msg->type.c_str(), own_msg->height, own_msg->weight.c_str());
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_message_subscriber");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/robot_message_topic", 10, own_message_callback);

    ros::spin();

    return 0;
}
