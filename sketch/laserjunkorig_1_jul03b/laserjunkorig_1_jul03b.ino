
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
int a = 1;

ros:: Publisher pub_Laser("LaserData", &CDLaser_msg);
ros::NodeHandle nh;

void setup() 
{
  nh.initNode();
  nh.advertise(pub_Laser);
  
  CDLaser_msg.header.frame_id = "laser_frame";
  CDLaser_msg.angle_min = 0;
  CDLaser_msg.angle_max = 0.1; //3.14;
  CDLaser_msg.angle_increment = 0.05; //1.57;
  CDLaser_msg.time_increment = 0.0125;
  CDLaser_msg.scan_time = 0.0;
  CDLaser_msg.range_min = 0.0;
  CDLaser_msg.range_max = 30000;

/*
  f_angle_min = -1.57;
  f_angle_max = 1.57;
  f_angle_increment = 0.785;  // 3.14/4   - 5 measurement points
  f_time_increment = 10;
  f_scan_time = 4;
  f_range_min = 0.1;
  f_range_max = 100000;
*/
  CDLaser_msg.ranges_length = 2;
//  CDLaser_msg.intensities_length = 1;

  // create the test data
/*  for (int z = 5 ; z<10; z++)
  {
    f_ranges[z] = z;
    f_intensities[z] = 2*z;
  } */
}

void loop() 
{
  if ((millis() - publisher_timer) > 100)
  {
    CDLaser_msg.header.stamp = nh.now();
/*    CDLaser_msg.header.frame_id = "laser_frame";
    CDLaser_msg.angle_min = 0;
    CDLaser_msg.angle_max = 3.1;
    CDLaser_msg.angle_increment = 0.785;
    CDLaser_msg.time_increment = 10;
    CDLaser_msg.scan_time = 4;
    CDLaser_msg.range_min = 0.1;
    CDLaser_msg.range_max = 30;
*/
    for (int z = 0 ; z<2; z++)
    {
      CDLaser_msg.ranges[z] = a; //f_ranges[z];
    }
    ++a;
/*    for (int z = 0 ; z<5; z++)
    {
      CDLaser_msg.intensities[z] = f_intensities[z];
    }
*/
//    CDLaser_msg.intensities[0] = 10;
//    CDLaser_msg.ranges[0] = 15;
    pub_Laser.publish(&CDLaser_msg);
    publisher_timer = millis() + 100;
  }
  nh.spinOnce();
//  delay(1000);
}
