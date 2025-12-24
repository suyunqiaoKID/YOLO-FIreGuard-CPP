#include <iostream>
#include <chrono>
#include <direct.h>
#include <windows.h>
#include "Detector.hpp"

#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace cv;

string getTimestamp() {
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    struct tm buf; localtime_s(&buf, &t);
    char s[100]; strftime(s, sizeof(s), "%Y%m%d_%H%M%S", &buf);
    return string(s);
}

int main() {
    _mkdir("logs");
    
    // ³õÊ¼»¯¼ì²âÆ÷
    Detector fire_detector("models/best.onnx", true);

    VideoCapture cap(0);
    if (!cap.isOpened()) return -1;

    int fire_counter = 0;
    const int ALARM_LIMIT = 15;
    bool is_alarming = false;

    Mat frame;
    while (cap.read(frame)) {
        // Ö´ÐÐÍÆÀí
        auto results = fire_detector.run_inference(frame);

        if (!results.empty()) {
            fire_counter++;
        } else {
            fire_counter = max(0, fire_counter - 1);
        }

        // ±¨¾¯Âß¼­
        if (fire_counter >= ALARM_LIMIT) {
            rectangle(frame, Rect(0,0, frame.cols, frame.rows), Scalar(0,0,255), 10);
            putText(frame, "FIRE ALARM!", Point(50, 100), FONT_HERSHEY_DUPLEX, 2, Scalar(0,0,255), 3);
            Beep(1000, 100);

            if (!is_alarming) {
                string path = "logs/fire_" + getTimestamp() + ".jpg";
                imwrite(path, frame);
                cout << "Alarm logged: " << path << endl;
                is_alarming = true;
            }
        } else {
            is_alarming = false;
        }

        // »æÖÆÆÕÍ¨¼ì²â¿ò
        for (const auto& det : results) {
            rectangle(frame, det.box, Scalar(0, 255, 0), 2);
        }

        imshow("FireGuard Pro", frame);
        if (waitKey(1) == 27) break;
    }

    return 0;
}