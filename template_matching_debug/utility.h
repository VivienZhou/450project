
#ifndef UTILITY_H
#define UTILITY_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

const double PI = 3.14159265359;

struct center_and_angle_t {
    cv::Point center;
    double angle;
};


#endif