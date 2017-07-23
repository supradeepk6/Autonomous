#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/UInt8MultiArray.h>

int val [61];
int flag = 0;
int num_read = 61;

void chatterCallback(const std_msgs::UInt8MultiArray::ConstPtr& msg)
{
  for(unsigned int i = 0; i < num_read; ++i) 
  {
    ROS_INFO("I heard: [%d]", msg->data[i]);
    val[i] = msg->data[i];
  }
  flag = 100;
}

int main(int argc, char** argv){
  
  ros::init(argc, argv, "laser_scan_publisher");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scanlite", 100);

  
  double ranges[num_read];

  ros::Rate r(1.0);

  while(n.ok()){
    ros::Time scan_time = ros::Time::now();

    //populate the LaserScan message
    sensor_msgs::LaserScan scan;
    scan.header.stamp = scan_time;
    scan.header.frame_id = "laser";
    scan.angle_min = 0.698;
    scan.angle_max = 2.792;
    scan.angle_increment = 2.094/num_read;
    scan.time_increment = 0.025/num_read;
    scan.range_min = 0.0;
    scan.range_max = 500.0;

    scan.ranges.resize(num_read);

    if (flag == 100)
    {
      for(unsigned int i = 0; i < num_read; ++i)
      {
      scan.ranges[i] = val[i];
      }
      flag = 0;
    }
  
//    if(i == 240){
    scan_pub.publish(scan);
//    }
    ros::spinOnce();
    r.sleep();
  }
}
/*
int main(int argc, char** argv){
  ros::init(argc, argv, "laser_scan_publisher");

  ros::NodeHandle n;
  ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan", 50);

  unsigned int num_readings = 100;
  double laser_frequency = 40;
  double ranges[num_readings];
 // double intensities[num_readings];

  int count = 0;
  ros::Rate r(1.0);
  while(n.ok()){
    //generate some fake data for our laser scan
    for(unsigned int i = 0; i < num_readings; ++i){
      ranges[i] = count;
 //     intensities[i] = 100 + count;
    }
    ros::Time scan_time = ros::Time::now();

    //populate the LaserScan message
    sensor_msgs::LaserScan scan;
    scan.header.stamp = scan_time;
    scan.header.frame_id = "laser_frame";
    scan.angle_min = 0;
    scan.angle_max = 6.28;
    scan.angle_increment = 6.28 / num_readings;
    scan.time_increment = (1 / laser_frequency) / (num_readings);
    scan.range_min = 0.0;
    scan.range_max = 100.0;

    scan.ranges.resize(num_readings);
    scan.intensities.resize(num_readings);
    for(unsigned int i = 0; i < num_readings; ++i){
      scan.ranges[i] = ranges[i];
  //    scan.intensities[i] = intensities[i];
    }

    scan_pub.publish(scan);
    ++count;
    r.sleep();
  }
}
*/
