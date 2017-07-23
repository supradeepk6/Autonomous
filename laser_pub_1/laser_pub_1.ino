#include <Wire.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <Wire.h>
#include <LIDARLite.h>

ros::NodeHandle  nh;

std_msgs::Int16 dist_msg;
ros::Publisher pub_dist("chatter", &dist_msg);

LIDARLite myLidarLite;

void setup()
{
  nh.initNode();
  nh.advertise(pub_dist);
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);
}

long publisher_timer;

void loop()
{
  
  if (millis() > publisher_timer) 
  {
      dist_msg.data = myLidarLite.distance();
      pub_dist.publish(&dist_msg);
      publisher_timer = millis() + 10;
  }
  
  nh.spinOnce();
}
