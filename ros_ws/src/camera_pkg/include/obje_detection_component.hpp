#ifndef CAMERA_PKG__DETECTION_NODE_HPP_
#define CAMERA_PKG__DETECTION_NODE_HPP_


#include <chrono>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <memory>
#include <vector>

#include "visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/opencv.hpp>

using std::placeholders::_1;


namespace object_detection_composition
{
    class DetectionComponent final : public rclcpp::Node
    {
    public:
        explicit DetectionComponent(const rclcpp::NodeOptions& options) : Node("detection", options)
        {
            std::string topic_subscriber_name = "camera/image_raw";
            std::string topic_publisher_name = "camera/object_detection";

            try{

                auto net = cv::dnn::readNet("yolov5s.onnx");
                
            } catch (const std::exception& e){

                RCLCPP_ERROR(get_logger(), "Error while loading pretrained weights %s", e.what());
                throw;
            }

            publisher_m = this->create_publisher<sensor_msgs::msg::Image>(topic_publisher_name, 10);
            thread_m = std::thread(std::bind(&DetectionComponent::callback_publisher, this));        

            subcription_m = this->create_subscription<sensor_msgs::msg::Image>(topic_subscriber_name, 10, std::bind(&DetectionComponent::callback_subscriber, this, _1));
        }

        ~DetectionComponent()
        {
            if (thread_m.joinable()){
                thread_m.join();
            }
        }

    
        void callback_publisher();
        void callback_subscriber(const sensor_msgs::msg::Image::UniquePtr msg);
        std::string mat_type2encoding(int mat_type);
        cv::Mat format_yolov5(const cv::Mat& source);
        std::vector<cv::Mat> getPredictions();

    private:
    cv::VideoCapture cap_m;
    cv::Mat frame_m;
    std::thread thread_m;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_m;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subcription_m;
    };
}
#endif