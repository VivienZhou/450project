//
//  crop_img.h
//  own_template_matching
//
//  Created by 鲁又佳 on 7/18/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

#ifndef CROP_IMG_H
#define CROP_IMG_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "utility.h"
#include <iostream>
#include <cmath>

cv::Mat crop_img(const cv::Mat &original_img, cv::Point &upper_left_corner, double crop_size, const cv::Point crop_center, double resize_factor);

#endif
