#include <Wire.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <Wire.h>
#include <LIDARLite.h>
#include <Servo.h>
#include <std_msgs/Int16MultiArray.h>

ros::NodeHandle  nh;

std_msgs::Int16MultiArray dist_msg;
ros::Publisher pub_dist("chatter", &dist_msg);

Servo myservo;
int pos = 0;
LIDARLite myLidarLite;

void setup()
{
  nh.initNode();
  dist_msg.layout.dim = (std_msgs::MultiArrayDimension *)
  malloc(sizeof(std_msgs::MultiArrayDimension)*2);
  dist_msg.layout.dim[0].label = "height";
  dist_msg.layout.dim[0].size = 31;
  dist_msg.layout.dim[0].stride = 1*31;
  dist_msg.layout.data_offset = 0;
  dist_msg.data = (int *)malloc(sizeof(int)*31);
  dist_msg.data_length = 31;
  nh.advertise(pub_dist);
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);
  myservo.attach(9);
}

void loop()
{
    int i = 0;
//    int j = 0;

      for(pos = 40; pos < 160; pos += 4)
      {
        myservo.write(pos); 
        dist_msg.data[i] = myLidarLite.distance();
        i = i+1;
        delay(15);
      }
      pub_dist.publish(&dist_msg);
      nh.spinOnce();
      i = 0;
      myservo.write(40);
      delay(100);
}
//  publisher_timer = millis() + 10;
//  }
/*  
      for(pos = 160; pos>=40; pos-=1) 
      {                                
        myservo.write(pos);
        dist_msg.data[j] = myLidarLite.distance();
        pub_dist.publish(&dist_msg);
        nh.spinOnce();
        j = j+1;
        delay(15);
      }
      j = 0;
      
} */
