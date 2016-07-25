//
//  resize_img.cpp
//  own_template_matching
//
//  Created by 鲁又佳 on 7/13/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

#include "resize_img.h"

using namespace std;
using namespace cv;

int resize_img(const Mat &original_img, Mat &resized_img, double resize_factor) {
    resize(original_img, resized_img, Size(), resize_factor, resize_factor, INTER_NEAREST);
    return 0;
}
