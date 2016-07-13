//
//  resize_and_get_location_and_rotation.cpp
//  own_template_matching
//
//  Created by 鲁又佳 on 7/13/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

#include "resize_and_get_location_and_rotation.h"

using namespace std;
using namespace cv;

center_and_angle_t resize_and_get_location_and_rotation(const cv::Mat &templ_img, const cv::Mat &test_img) {
    double resize_factor = 0.5;
    Mat resized_test_img, resized_templ_img;
    resize(test_img, resized_test_img, Size(), resize_factor, resize_factor, INTER_NEAREST);
    resize(templ_img, resized_templ_img, Size(), resize_factor, resize_factor, INTER_NEAREST);
    
    // calculate the rotation angle and center location in the resized test image
    center_and_angle_t resized_center_and_angle = get_location_and_rotation(resized_templ_img, resized_test_img);
    
    // get the range of the part to crop
    int tolerance = 1;
    
    double crop_size = sqrt(templ_img.cols * templ_img.cols + templ_img.rows * templ_img.rows);
    int row_start = max(0, static_cast<int>((resized_center_and_angle.center.y - tolerance) / resize_factor - crop_size / 2));
    int row_end = min(test_img.rows - 1, static_cast<int>((resized_center_and_angle.center.y + tolerance) / resize_factor + crop_size / 2));
    int col_start = max(0, static_cast<int>((resized_center_and_angle.center.x - tolerance) / resize_factor - crop_size / 2));
    int col_end = min(test_img.cols - 1, static_cast<int>((resized_center_and_angle.center.x + tolerance) / resize_factor + crop_size / 2));
    
    // record the location of the upper-left corner of the cropped image
    Point upper_left_corner = Point(col_start, row_start);
    
    // copy the cropped to a new Mat
    Rect myROI(col_start, row_start, col_end - col_start + 1, row_end - row_start + 1);
    Mat cropped_test_img(test_img, myROI);
    
    //imshow("cropped image", cropped_test_img);
    
    double angle_tolerance = 20;
    double rough_angle = 360 - radians_to_degree(resized_center_and_angle.angle);
    double angle_start = rough_angle - angle_tolerance;
    double angle_end = rough_angle + angle_tolerance;
    center_and_angle_t result_center_and_angle = get_location_and_rotation(templ_img, cropped_test_img, angle_start, angle_end, 1);
    
    // change the center coordinates into the coordinates in the original test image
    result_center_and_angle.center.x += upper_left_corner.x;
    result_center_and_angle.center.y += upper_left_corner.y;
    
    return result_center_and_angle;
    
}