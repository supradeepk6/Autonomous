#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int16MultiArray.h>

ros::NodeHandle nh;

std_msgs::Int16MultiArray arr;
ros::Publisher pub_arr( "chatter", &arr);

void setup() {
  nh.initNode();
  arr.layout.dim = (std_msgs::MultiArrayDimension *)
  malloc(sizeof(std_msgs::MultiArrayDimension)*2);
  arr.layout.dim[0].label = "height";
  arr.layout.dim[0].size = 121;
  arr.layout.dim[0].stride = 1*121;
  arr.layout.data_offset = 0;
  arr.data = (int *)malloc(sizeof(int)*121);
  arr.data_length = 121;
  nh.advertise(pub_arr);
}
int count = 0;
void loop() 
  {    
  for(int i = 0; i < 121; i++){
    arr.data[i] = i+count;
  } 
  pub_arr.publish(&arr);
  nh.spinOnce();
  delay(500);
  count++;
}
