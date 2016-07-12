//
//  find_object.h
//  test
//
//  Created by 黄 天豪 on 16/7/11.
//  Copyright © 2016年 Tianhao Huang. All rights reserved.
//

#ifndef find_object_h
#define find_object_h

#include "utility.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
using namespace cv;

bool is_highest(int row, int col, int nearby_size, Mat value);
vector<center_and_angle_t> find_object(Mat value, Mat angle, int nearby_size);


#endif /* find_object_h */


