
#ifndef ANNOTATION_H
#define ANNOTATION_H

#include "utility.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

void draw_boundary(const std::vector<center_and_angle_t>& multi_object_info, int scaleCol, int scaleRow, cv::Mat& test_img);

#endif 