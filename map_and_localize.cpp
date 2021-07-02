Map and Localize a robot

- create a package named my_mapping_launcher
- inside it mkdir launch
- inside it touch my_gmapping.launch
- roscd turtlebot_navigation
- cp gmapping.launch.xml /home/user/catkin_ws/src/my_mapping_launcher/launch/my_gmapping.launch

Modifiy the following according to your robot
scan_topic (from which topic the laser data is obtained)
base_frame (the name of the frame attached to the center of the mobile base, default "base_link"
odom_frame (the name of the framte atteched to the odometry system)

launch the gmapping code
roslaunch my_mapping_laucnher my_mapping.launch

launch the keyboard teleop to move the robot
roslaunch summit_xl_gazebo keyoboardteleop

start the map provider with the saved map
rosrun map_server map_server map_file.yaml

how to localize a robot
go to turtlebot_navigation and copy amcl.launch.xml to your
folder




