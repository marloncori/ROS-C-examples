#include "ros/ros.h"
#include "tutorials2/Robot.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_message_publisher");
    ros::NodeHandle nh;

    ros::Publisher robot_message_pub = nh.advertise<tutorials2::Robot>("/robot_message_topic", 10);

    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        tutorials2::Robot own_msg;
        own_msg.name = "H327Y";
        own_msg.DOF = 19;
        own_msg.type = "biped";
        own_msg.height = 46;
        own_msg.weight = "2.5 kg";

        robot_message_pub.publish(own_msg);

        ROS_INFO("Publish robot Info: name:%s  DOF:%d  type:%s  height:%d  weight:%s",own_msg.name.c_str(), own_msg.DOF, own_msg.type.c_str(), own_msg.height, own_msg.weight.c_str());

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
