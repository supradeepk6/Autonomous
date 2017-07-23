This is a project which provides every project with the publisher and subscriber interface.

The way to use this project is shown in the publisher_subscriber_node.cpp file.

Following is the way to use the publisher and subscriber from the command line. Currently the topics are fixed, but the flexibility of topics can be released in next commits.

Subscriber: rosrun publisher_subscriber publisher_subscriber_node listener

Publisher: rosrun publisher_subscriber publisher_subscriber_node talker "This is the data to be sent"


