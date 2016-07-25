//
//  get_accurate_center_and_rotation.h
//  own_template_matching
//
//  Created by 鲁又佳 on 7/18/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

#ifndef GET_ACCURATE_CENTER_AND_ROTATION_H
#define GET_ACCURATE_CENTER_AND_ROTATION_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "utility.h"
#include "get_location_and_rotation.h"

center_and_angle_t get_accurate_center_and_angle(const cv::Mat& test_img, const cv::Mat& templ_img, cv::Point upper_left_corner, double angle);

#endif
