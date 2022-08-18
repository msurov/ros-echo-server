#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int64.h>
#include <sstream>
#include "time.h"


class EchoServer
{
    ros::Subscriber sub_;
    ros::Publisher pub_;
    ros::NodeHandle node_;
public:
    void cb(const std_msgs::Int64::ConstPtr& msg)
    {
        auto value = msg->data;
        auto answer = std_msgs::Int64();
        answer.data = value;
        pub_.publish(answer);
    }

    EchoServer()
    {
        sub_ = node_.subscribe("echoinp", 1, &EchoServer::cb, this);
        pub_ = node_.advertise<std_msgs::Int64>("echoout", 1);
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "echosrv");
    EchoServer srv;
    ros::spin();
    return 0;
}
