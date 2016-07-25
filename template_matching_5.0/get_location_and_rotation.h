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
#include "utility.h"
#include <iostream>
#include <cmath>
#include <string>

// Calculate the coordinates of the point in original test image before rotation
// return a center_and_angle_t with the rotation angle and the original coordinates
center_and_angle_t cal_original_coordinate(int rotated_image_rows, int rotated_image_cols,
                                           int image_rows, int image_cols,
                                           int rotated_coord_row, int rotated_coord_col,
                                           double rotation_angle);

// Rotate the input_img with a given angle, and crop the rotated image so that
// the Mat can perfectly fit the rotated image
cv::Mat rotate_and_crop(const cv::Mat &input_img, double angle, const cv::Rect &ROI, bool is_int = true);

// First call rotate_and_crop on test_img, and then call matchTemplate on templ_img and
// the processed test_img.
// This function returns a Mat with similarity scores of each pixel
cv::Mat cal_similarity_score(const cv::Mat &templ_img, const cv::Mat &test_img, double angle);

// Get the location of the BEST match and the rotation angle
// return a center_and_angle with the corresponding information
center_and_angle_t get_location_and_rotation(const cv::Mat &templ_img, const cv::Mat &test_img, double rotation_start = 0, double rotation_end = 360, double rotation_stride = 1);

#endif 
