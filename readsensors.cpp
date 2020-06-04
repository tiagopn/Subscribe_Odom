#include "readsensors.h"
// #include "../include/my_code/readsensors.h"


int main(int argc, char **argv){

    ros::init(argc, argv, "readsensors");
    ros::NodeHandle node;

    //publisher
    ros::Publisher landmark_pub = node.advertise<Robots>("closest_landmark", 10);

    //subscriber
    LandmarkMonitor monitor(landmark_pub);
    ros::Subscriber sub = node.subscribe("odom", 10, &LandmarkMonitor::OdomCallback, &monitor);
    ros::spin();
    return 0;
}