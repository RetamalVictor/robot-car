#include <opencv2/opencv.hpp>


void load_net(cv::dnn::Net &net, bool is_cuda)
{
    auto result = cv::dnn::readNet("config_files/yolov5s.onnx");
    if (is_cuda)
    {
        std::cout << "Attempty to use CUDA\n";
        result.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
        result.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
    }
    else
    {
        std::cout << "Running on CPU\n";
        result.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        result.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    }
    net = result;
}


int main(int, char **)
{
    cv::dnn::Net net;
    load_net(net, false);

    // auto net = cv::dnn::readNet("/home/victor/code/diff_robot/scripts/yolov5s.onnx");
    
    return 0;
}