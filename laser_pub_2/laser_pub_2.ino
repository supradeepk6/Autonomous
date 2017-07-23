#include <Wire.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <Wire.h>
#include <LIDARLite.h>
#include <Servo.h>

ros::NodeHandle  nh;

std_msgs::Int16 dist_msg;
ros::Publisher pub_dist("chatter", &dist_msg);

Servo myservo;
int pos = 0;
LIDARLite myLidarLite;

void setup()
{
  nh.initNode();
  nh.advertise(pub_dist);
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);
  myservo.attach(9);
}

long publisher_timer;

void loop()
{
  
//  if (millis() > publisher_timer) 
//  {
      for(pos = 40; pos < 160; pos += 1)
      {
        myservo.write(pos); 
        dist_msg.data = myLidarLite.distance();
        pub_dist.publish(&dist_msg);
        nh.spinOnce();
        delay(15);
      }
//  publisher_timer = millis() + 10;
//  }
  
      for(pos = 160; pos>=40; pos-=1) 
      {                                
        myservo.write(pos);
        dist_msg.data = myLidarLite.distance();
        pub_dist.publish(&dist_msg);
        nh.spinOnce();
        delay(15);
      }
}
