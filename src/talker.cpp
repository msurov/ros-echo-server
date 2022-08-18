#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int64.h>
#include <sstream>
#include "time.h"


void answercb(const std_msgs::Int64::ConstPtr& msg)
{
  int64_t value = msg->data;
  std::cout << "ellapsed " << get_epoch_usec() - value << "usec" << std::endl;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle node;
  ros::Publisher pub = node.advertise<std_msgs::Int64>("echoinp", 1);
  ros::Subscriber sub = node.subscribe("echoout", 1, answercb);
  ros::Rate rate(100);
  ros::AsyncSpinner spinner(1);
  spinner.start();

  while (ros::ok())
  {
    std_msgs::Int64 msg;
    msg.data = get_epoch_usec();
    pub.publish(msg);
    rate.sleep();
  }

  return 0;
}
