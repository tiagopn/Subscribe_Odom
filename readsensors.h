#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "std_msgs/String.h"
#include "../include/stl.h"

#include "/home/jarvis/catkin_ws/devel/include/my_code/Robots.h"  //Robots e' a msg

using std::vector;
using std::string;
using my_code::Robots;

class Landmark{
    public:
        Landmark(string name, double x, double y): name(name), x(x), y(y) {

        }
        string name;
        double x;
        double y;
};

class LandmarkMonitor{
    public: 
         //Modificado para ter tambem o PUBLISHER
        LandmarkMonitor(const ros::Publisher&  landmark_pub): 
            landmarks_(), landmark_pub_(landmark_pub) {
            InitLandmarks();
        }

        void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
            double x =  msg->pose.pose.position.x;
            double y =  msg->pose.pose.position.y;
            Robots ld = FindClosest(x, y);
            landmark_pub_.publish(ld);  //para o PUBLISHER
            // ROS_INFO("name: %s, distance: %f", ld.name.c_str(), ld.distance);
            //ROS_INFO("x: [%f], y: [%f]", x, y);
        }

    private:
        vector<Landmark> landmarks_;
        ros::Publisher landmark_pub_; //para o PUBLISHER

        // Modificar toda parte abaixo em caso de modificar o mapa
        // OBS.: localizacao baseada em marcos naturais
        Robots FindClosest(double x, double y){

            Robots result;
            result.distance = -1;

            for (size_t i=0; i<landmarks_.size(); i++){
                const Landmark& landmark = landmarks_[i];
                double xd = landmark.x - x;
                double yd = landmark.y - y;
                double distance = sqrt(xd*xd + yd*yd);

                if (result.distance < 0 || distance < result.distance){
                    result.name = landmark.name;
                    result.distance = distance;
                }
            }
            return result;
        }

        void InitLandmarks(){
            landmarks_.push_back(Landmark("Cubo", 0.31, -0.99));
            landmarks_.push_back(Landmark("Container", 0.11, -2.42));
            landmarks_.push_back(Landmark("Cilindro", -1.14, -2.88));
            landmarks_.push_back(Landmark("Barreira", -2.59, -0.83));
            landmarks_.push_back(Landmark("Estante", -0.09, 0.53));
        }
};