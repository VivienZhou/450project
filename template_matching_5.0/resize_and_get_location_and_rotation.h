//
//  resize_and_get_location_and_rotation.h
//  own_template_matching
//
//  Created by 鲁又佳 on 7/13/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

#ifndef RESIZE_AND_GET_LOCATION_AND_ROTATION_H
#define RESIZE_AND_GET_LOCATION_AND_ROTATION_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "utility.h"
#include "get_location_and_rotation.h"
#include <iostream>
#include <cmath>

center_and_angle_t resize_and_get_location_and_rotation(const cv::Mat &templ_img, const cv::Mat &test_img);


#endif 
