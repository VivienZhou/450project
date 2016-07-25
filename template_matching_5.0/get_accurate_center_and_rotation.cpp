//
//  get_accurate_center_and_rotation.cpp
//  own_template_matching
//
//  Created by 鲁又佳 on 7/18/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

#include "get_accurate_center_and_rotation.h"

using namespace cv;

center_and_angle_t get_accurate_center_and_angle(const Mat& test_img, const Mat& templ_img, Point upper_left_corner, double angle) {
    double angle_tolerance = 20;
    double rough_angle = 360 - radians_to_degree(angle);
    double angle_start = rough_angle - angle_tolerance;
    double angle_end = rough_angle + angle_tolerance;
    center_and_angle_t result_center_and_angle = get_location_and_rotation(templ_img, test_img, angle_start, angle_end, 1);
    
    // change the center coordinates into the coordinates in the original test image
    result_center_and_angle.center.x += upper_left_corner.x;
    result_center_and_angle.center.y += upper_left_corner.y;
    
    return result_center_and_angle;
}
