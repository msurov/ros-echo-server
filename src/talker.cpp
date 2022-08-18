#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int64.h>
#include <sstream>
#include "time.h"

class Talker
{
  ros::NodeHandlePtr node_;
  ros::Subscriber sub_;
  ros::Publisher pub_;
  ros::Timer timer_;

public:
  void timercb(const ros::TimerEvent& event)
  {
    std_msgs::Int64 msg;
    msg.data = get_epoch_usec();
    pub_.publish(msg);
  }

  void answercb(const std_msgs::Int64::ConstPtr& msg)
  {
    int64_t value = msg->data;
    std::cout << "ellapsed " << get_epoch_usec() - value << "usec" << std::endl;
  }

  Talker()
  {
    node_.reset(new ros::NodeHandle("talker"));
    sub_ = node_->subscribe("echoout", 1, &Talker::answercb, this);
    pub_ = node_->advertise<std_msgs::Int64>("echoinp", 10);
    timer_ = node_->createTimer(1.0, &Talker::timercb, this, false, true);
    timer_.setPeriod(ros::Duration(0.1));
    timer_.start();
  }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  Talker talker;
  ros::spin();
  return 0;
}
