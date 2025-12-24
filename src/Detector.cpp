#include "Detector.hpp"

Detector::Detector(const std::string& model_path, bool use_cuda) {
    net = cv::dnn::readNetFromONNX(model_path);
    if (use_cuda) {
        net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
        net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    }
}

std::vector<Detection> Detector::run_inference(const cv::Mat& frame) {
    std::vector<Detection> detections;

    // 1. 预处理 (Blob)
    cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0 / 255.0, input_size, cv::Scalar(), true, false);
    net.setInput(blob);

    // 2. 前向传播
    std::vector<cv::Mat> outs;
    net.forward(outs, net.getUnconnectedOutLayersNames());

    // 3. 后处理 YOLOv8 输出 [1, 5, 8400]
    cv::Mat output = outs[0];
    if (output.dims == 3) {
        output = output.reshape(1, output.size[1]); // [5, 8400]
        cv::transpose(output, output);              // [8400, 5]
    }

    std::vector<cv::Rect> boxes;
    std::vector<float> confs;
    std::vector<int> class_ids;

    float rx = (float)frame.cols / input_size.width;
    float ry = (float)frame.rows / input_size.height;

    for (int i = 0; i < output.rows; ++i) {
        float confidence = output.at<float>(i, 4);
        if (confidence > conf_threshold) {
            float cx = output.at<float>(i, 0);
            float cy = output.at<float>(i, 1);
            float w = output.at<float>(i, 2);
            float h = output.at<float>(i, 3);

            int left = int((cx - 0.5 * w) * rx);
            int top = int((cy - 0.5 * h) * ry);
            int width = int(w * rx);
            int height = int(h * ry);

            boxes.push_back(cv::Rect(left, top, width, height));
            confs.push_back(confidence);
            class_ids.push_back(0); // 假设只有一类：Fire
        }
    }

    // 4. 非极大值抑制 (NMS)
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confs, conf_threshold, nms_threshold, indices);

    for (int idx : indices) {
        Detection det;
        det.box = boxes[idx];
        det.confidence = confs[idx];
        det.class_id = class_ids[idx];
        detections.push_back(det);
    }

    return detections;
}