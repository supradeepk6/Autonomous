#include <iostream>
#include <ros/ros.h>
#include <publisher_subscriber/pub_sub.hpp>
#include <std_msgs/String.h>

using namespace ros;
// This project is mainly used for the publishing and subsribing of data.
// Everywhere in the project, you have to use this publisher and subscriber thing.
// There is no need to create any special pub sub models in your classes.

ros::Subscriber sub;

void callback_temp(const std_msgs::String::ConstPtr &msg)
{
    ROS_INFO("publisher_subscriber_node: Data Received: [%s]", msg->data.c_str());
}

int main(int argc, char *argv[])
{
    ros::NodeHandle node_handle;

    if(!strcmp(argv[1], "talker"))
    {
        string send_data(argv[2]);
        cout << "Talker" << endl;

        msg_details publish_details;
        publish_details.is_talker = true;
        publish_details.is_listener = false;
        publish_details.pub_repeat = true;
        publish_details.frequency = 1;
        publish_details.message_topic = "test/topic";
        Pub_Sub publisher;
        publisher.init(node_handle, publish_details, sub);

        ros::Rate loop_rate(publish_details.frequency);
        while(ros::ok())
        {
            // Publishing data
            publisher.publisher_data(send_data);
            loop_rate.sleep();
        }
    }
    else if(!strcmp(argv[1], "listener"))
    {
        cout << "Listener" << endl;

        msg_details subscribe_details;
        subscribe_details.is_talker = false;
        subscribe_details.is_listener = true;
        subscribe_details.pub_repeat = false;
        subscribe_details.message_topic = "test/topic";
        subscribe_details.received_callback = callback_temp;
        Pub_Sub subscriber;
        subscriber.init(node_handle, subscribe_details, sub);
    }

    return 0;
}
