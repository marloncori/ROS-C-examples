#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include <iostream>

geometry_msgs::Pose2D goal;

using namespace std;

void set_goal()
{
    cout << "enter goal x: ";
    cin >> goal.x;
    cout << goal.x << " now y: " << endl;
    cin >> goal.y;
    cout << endl;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "simple_goal_pub");
    ros::NodeHandle node;

    ros::Publisher pubGoal = node.advertise<geometry_msgs::Pose2D>("waypoint", 0);

    while (ros::ok())
    {

        set_goal();
        pubGoal.publish(goal);
        cout << "publishing" << endl;
   
    }

    return 0;
}
