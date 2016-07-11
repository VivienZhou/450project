//
//  get_location_and_rotation.h
//
//  Created by 鲁又佳 on 7/11/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

#ifndef GET_LOCATION_AND_ROTATION_H
#define GET_LOCATION_AND_ROTATION_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cmath>
#include <string>

const double PI = 3.14159265359;

struct center_and_angle_t {
    cv::Point center;
    double angle;
};

center_and_angle_t cal_original_coordinate(int rotated_image_rows, int rotated_image_cols,
                                           int image_rows, int image_cols,
                                           int rotated_coord_row, int rotated_coord_col,
                                           double rotation_angle);

cv::Mat rotate_and_crop(cv::Mat input_img, double angle, cv::Rect ROI);

cv::Mat cal_similarity_score(cv::Mat templ_img, cv::Mat test_img, double angle);

center_and_angle_t get_location_and_rotation(cv::Mat templ_img, cv::Mat test_img, double rotation_start = 0, double rotation_end = 360, double rotation_stride = 1);

#endif 
