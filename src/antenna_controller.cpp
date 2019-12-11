#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string.h>
#include "sensor_msgs/NavSatFix.h"
#include <sstream>

double Longitude, Latitude, Altitude;
bool AutoMode = true;

void MoveAntennaCallback(const std_msgs::String::ConstPtr& msg);
void AntennaPositionCallback(const sensor_msgs::NavSatFix& msg);
void RoverPositionCallback(const std_msgs::String::ConstPtr& msg);

int main(int argc, char **argv)
{
    ros::init(argc, argv, "AutoControl",0);
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("MoveAntenna", 1000, MoveAntennaCallback);
    ros::Subscriber sub2 = n.subscribe("nmea_topic_driver", 1000, AntennaPositionCallback);
    ros::Subscriber sub3 = n.subscribe("RoverPos", 1000, RoverPositionCallback);
    ros::Rate loop_rate(10);
    
    while(ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

void MoveAntennaCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("Target angle: [%s]", msg->data.c_str());
}

void AntennaPositionCallback(const sensor_msgs::NavSatFix& msg)
{
    Longitude = msg.longitude;
    Latitude = msg.latitude;
    Altitude = msg.altitude;
}

void RoverPositionCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("Rover Position: [%s]", msg->data.c_str());
}