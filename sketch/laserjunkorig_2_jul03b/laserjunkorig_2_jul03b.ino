
#include "math.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// ROS includes
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/LaserScan.h>
#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

sensor_msgs::LaserScan CDLaser_msg;

/*
float f_angle_min;
float f_angle_max;
float f_angle_increment;
float f_time_increment;
float f_scan_time;
float f_range_min;
float f_range_max; */
//float f_ranges[5]; // max of 30 measurements
//float f_intensities[5]; 
//float rand = 50;

int publisher_timer;
//int a = 5;

ros:: Publisher pub_Laser("LaserData", &CDLaser_msg);
ros::NodeHandle nh;

void setup() 
{
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);
  
  nh.initNode();
  nh.advertise(pub_Laser);
  
  CDLaser_msg.header.frame_id = "laser_frame";
  CDLaser_msg.angle_min = 0;
  CDLaser_msg.angle_max = 0.1;
  CDLaser_msg.angle_increment = 0.05;
  CDLaser_msg.time_increment = 0.0125;
  CDLaser_msg.scan_time = 0.0;
  CDLaser_msg.range_min = 0.0;
  CDLaser_msg.range_max = 500;

/*
  f_angle_min = 0;
  f_angle_max = 10;
  f_angle_increment = 1;  // 3.14/4   - 5 measurement points
  f_time_increment = 10;
  f_scan_time = 4;
  f_range_min = 0.1;
  f_range_max = 10;
*/
  CDLaser_msg.ranges_length = 2;
 // CDLaser_msg.intensities_length = 1;

  // create the test data
/*  for (int z = 5 ; z<10; z++)
  {
    f_ranges[z] = z;
    f_intensities[z] = 2*z;
  } */
}

void loop() 
{
  if ((millis() - publisher_timer) > 1000)
  {
    CDLaser_msg.header.stamp = nh.now();
/*    CDLaser_msg.header.frame_id = "laser_frame";
    CDLaser_msg.angle_min = -1.57;
    CDLaser_msg.angle_max = 1.57;
    CDLaser_msg.angle_increment = 0.785;
    CDLaser_msg.time_increment = 10;
    CDLaser_msg.scan_time = 4;
    CDLaser_msg.range_min = 0.1;
    CDLaser_msg.range_max = 30;
*/
    for (int z = 0 ; z<2; z++)
    {
      CDLaser_msg.ranges[z] = myLidarLite.distance();
    }

/*    for (int z = 0 ; z<5; z++)
    {
      CDLaser_msg.intensities[z] = f_intensities[z];
    }
*/
//    CDLaser_msg.intensities[0] = 10;
//    CDLaser_msg.ranges[0] = myLidarLite.distance()/10;
    pub_Laser.publish(&CDLaser_msg);
    publisher_timer = millis() + 100;
  }
  nh.spinOnce();
  delay(1000);
}
