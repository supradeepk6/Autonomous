# Overview
This program is used for testing the localization of the robot as alternative to RVIZ tool by passing destination XY coordinates in an 
existing map while running the ROS wrapper AMCL application program. 

# Instructions
The following commands are executed in separate terminal windows,

$ roslaunch turtlebot_minimal bringup.launch

$ roslaunch rplidar_ros rplidar.launch

$ roslaunch turtlebot_navigation amcl_demo.launch

$ roslaunch turtlebot_rviz_navigation view_mapping.launch

$ sudo python Autonomous_Navigation.py

Note: Make sure you enter the coordinates in the python program before executing the application. 
