#ifndef GET_MULTI_LOCATION_AND_ROTATION_H
#define GET_MULTI_LOCATION_AND_ROTATION_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "get_location_and_rotation.h"
#include "find_object.h"
#include "utility.h"
#include <iostream>
#include <cmath>


vector<center_and_angle_t> get_multi_location_and_rotation(const cv::Mat & templ_img, const cv::Mat & test_img, int nearby_size, double threshold, double rotation_start = 0, double rotation_end = 360, double rotation_stride = 1);

void pair_wise_mat_max(cv::Mat & max_score, const cv::Mat & tmp_score, cv::Mat & best_pos, int angle);

#endif 




