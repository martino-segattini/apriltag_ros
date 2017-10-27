#pragma once

// ros
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>
#include <sensor_msgs/srv/set_camera_info.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <apriltag_msgs/msg/april_tag_detection.hpp>
#include <apriltag_msgs/msg/april_tag_detection_array.hpp>

// apriltag
#include <apriltag.h>
#include <common/pjpeg.h>

// default tag families
#include <tag16h5.h>
#include <tag25h7.h>
#include <tag25h9.h>
#include <tag36h10.h>
#include <tag36h11.h>
#include <tag36artoolkit.h>

#include <iomanip>


class AprilTag2Node : public rclcpp::Node {
public:
    AprilTag2Node();

    ~AprilTag2Node();

private:
    apriltag_family_t* tf;
    apriltag_detector_t* td;
    std::string tag_family;

    sensor_msgs::msg::CameraInfo camera_info;

    // function pointer for tag family creation / destruction
    static std::map<std::string, apriltag_family_t *(*)(void)> tag_create;
    static std::map<std::string, void (*)(apriltag_family_t*)> tag_destroy;

    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr sub_img;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr sub_info;
    rclcpp::Publisher<geometry_msgs::msg::TransformStamped>::SharedPtr pub_pose;
    rclcpp::Publisher<apriltag_msgs::msg::AprilTagDetectionArray>::SharedPtr pub_detections;

    void onImage(const sensor_msgs::msg::CompressedImage::SharedPtr msg_img);
};