
#ifndef ANNOTATION_H
#define ANNOTATION_H

#include "utility.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

void draw_boundary(const center_and_angle_t& object_info, int scaleCol, int scaleRow, cv::Mat& test_img);

#endif 