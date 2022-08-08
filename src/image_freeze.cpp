#include "ros/init.h"
#include "ros/node_handle.h"
#include "ros/rate.h"
#include "ros/ros.h"
#include "image_grab/imgfr.h"
#include "ros/subscriber.h"
#include "sensor_msgs/Image.h"
#include <cstdint>
#include <vector>

std::vector<unsigned char> im_array;

int width = 0;
int height = 0;

bool has_data = false;

bool grab(image_grab::imgfr::Request  &req, image_grab::imgfr::Response &res){
    res.im_data = im_array;
    return true;
}

class RlssSubscriber{
    ros::Subscriber sub;
    static void rlss_callback(const sensor_msgs::Image::ConstPtr &msg){
        width = msg->width;
        height = msg->height;

        im_array = msg->data;
    }
    public:
    RlssSubscriber(ros::NodeHandle n){
        this->sub = n.subscribe("camera/color/image_raw", 100, rlss_callback);
    }
};

int main(int argc, char **argv)
{
    
  ros::init(argc, argv, "image_freeze_server");
  ros::NodeHandle n;
  ros::Rate rate(100);

  RlssSubscriber rllss_sub(n);

  ros::ServiceServer service = n.advertiseService("image_freeze", grab);
  

  while(ros::ok()){
        ros::spinOnce();

        if (width*height != 0 && has_data == false){
            ROS_INFO("Ready to grab a %d x %d image!\n", width, height);
            has_data = true;
        }
        rate.sleep();

    }

  return 0;
}