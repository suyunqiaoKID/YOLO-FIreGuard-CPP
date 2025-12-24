#ifndef DETECTOR_H
#define DETECTOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <vector>
#include <string>

// 定义检测结果结构体
struct Detection {
    int class_id;
    float confidence;
    cv::Rect box;
};

class Detector {
public:
    // 构造函数：加载模型并配置 CUDA
    Detector(const std::string& model_path, bool use_cuda = true);

    // 推理函数：输入图像，返回检测到的目标列表
    std::vector<Detection> run_inference(const cv::Mat& frame);

private:
    cv::dnn::Net net;
    const cv::Size input_size = cv::Size(640, 640);
    const float conf_threshold = 0.5f;
    const float nms_threshold = 0.45f;
};

#endif