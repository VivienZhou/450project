#ifndef GET_MULTI_LOCATION_AND_ROTATION_H
#define GET_MULTI_LOCATION_AND_ROTATION_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "get_location_and_rotation.h"
#include "find_object.h"
#include "utility.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

vector<center_and_angle_t> get_multi_location_and_rotation(const Mat & templ_img, const Mat & test_img, double rotation_start = 0, double rotation_end = 360, double rotation_stride = 1);

void pair_wise_mat_max(Mat & max_score, const Mat & tmp_score, Mat & best_pos, int angle);

#endif 




