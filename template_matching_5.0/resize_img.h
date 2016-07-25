//
//  resize_img.h
//  own_template_matching
//
//  Created by 鲁又佳 on 7/13/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

#ifndef RESIZE_IMG_H
#define RESIZE_IMG_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "utility.h"
#include <iostream>

// Input: original image, a newly created Mat to contain resized image, a resize factor
// Output: an int showing successful or not
int resize_img(const cv::Mat &original_img, cv::Mat &resized_img, double resize_factor);

#endif 
