#include <iostream>
#include <memory>
#include <thread>

// OpenCv Libraries
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

// ZED Libraries
#include <zed/Camera.hpp>
#include <zed/utils/GlobalDefine.hpp>

// CUDA Libraries
#include <cuda.h>
#include <cuda_runtime_api.h>

// Local includes
#include <face_detect_module/face_detection_engine.hpp>

using namespace sl::zed;
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    bool is_live = false;
    string svo_file_path, svo_file_name(argv[2]), input_status(argv[1]);

    if(argc != 3) {
        cout << "Error in Usage:::Usage: <exe> [is_live]<true/false> <svo_file_name> <depth_clamp>" << endl;
        return -1;
    }

    int size_of_file_name = (sizeof(svo_file_name)/sizeof(char));

    if(!strcmp(input_status.c_str(), "true")) {
        is_live = true;
    }
    else {
        is_live = false;
    }

    if(!is_live) {
        cout << "From Stored Camera Feed" << endl;
        svo_file_path = "/media/ubuntu/7A1A38B11A386C6F/Video_Recordings/";
        svo_file_path.append(svo_file_name.c_str());
    }
    else {
        cout << "From Live Camera Feed" << endl;
    }

    cv::Mat temp(100, 100, CV_8UC4, 1);
    cv::imshow("Left", temp);

    face_detection_engine(is_live, svo_file_path);

    return 0;
}
