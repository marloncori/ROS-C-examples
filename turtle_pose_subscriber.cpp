#include "ros/ros.h"
#include "turtlesim/Pose.h"

void show_turtle_pose(const turtlesim::Pose::ConstPtr& pose_msg)
{
    ROS_INFO_STREAM("x position: " << pose_msg->x << "y position: " << pose_msg->y << "theta: " << pose_msg->theta);
    ROS_INFO_STREAM("linear velocity: " << pose_msg->linear_velocity << "angular velocity: " << pose_msg->angular_velocity);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_pose_subscriber");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/turtle1/pose", 1000, show_turtle_pose);

    ros::spin();

    return 0;
}
