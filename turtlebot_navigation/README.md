# GMapping for RPLIDAR
This is a turtlebot_navigation ROS package that uses GMapping algorithm for Simultaneous Localization and Mapping. However, the default 
parameters for the algorithm are designed for long range laser sensors such as Kinect Camera. The parameters are modified for RPLIDAR to 
generate a cleaner and accurate map. The parameters are located at
SPARbot/turtlebot_navigation/launch/includes/gmapping.launch

•	maxUrange = 5.5 

The maximum usable range of the laser in which the beam is clipped to this value.
-----------------------------------------------------------------------------------------------------------------------------------
•	maxRange = 5.4 

The maximum range of the sensor. The value is set less than maxUrange to show free space in the map, in regions with no obstacle within the range of the sensor.
-----------------------------------------------------------------------------------------------------------------------------------
•	minimumScore = 50 

This is used for considering the outcome of the scan matching good. The value is set at 50 to avoid experiencing jumping pose estimate issues.
-----------------------------------------------------------------------------------------------------------------------------------
•	linearUpdate = 0.2 

The parameter processes a scan each time the robot translates to the value set.
-----------------------------------------------------------------------------------------------------------------------------------
•	angularUpdate = 0.25 

The parameter processes a scan each time the robot rotates to the value set.
-----------------------------------------------------------------------------------------------------------------------------------
•	temporalUpdate = 5.0

The parameter processes a scan of the last scan processed is older than the update time in seconds.
-----------------------------------------------------------------------------------------------------------------------------------
•	delta = 0.025 

This sets the resolutions of the map.
-----------------------------------------------------------------------------------------------------------------------------------

## Map generated BEFORE modifying the parameters
![alt tag](https://github.com/SPARbot/turtlebot_navigation/blob/master/before_mod.png)

## Map generated AFTER modifiying the parameters
![alt tag](https://github.com/SPARbot/turtlebot_navigation/blob/master/after_mod.png)


