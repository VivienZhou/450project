//
//  crop_img.cpp
//  own_template_matching
//
//  Created by 鲁又佳 on 7/18/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

#include "crop_img.h"

using namespace cv;
using namespace std;

Mat crop_img(const Mat &original_img, Point &upper_left_corner, double crop_size, const Point crop_center, double resize_factor) {
    int tolerance = 1;
    
    // double crop_size = sqrt(templ_img.cols * templ_img.cols + templ_img.rows * templ_img.rows);
    int row_start = max(0, static_cast<int>((crop_center.y - tolerance) / resize_factor - crop_size / 2));
    int row_end = min(original_img.rows - 1, static_cast<int>((crop_center.y + tolerance) / resize_factor + crop_size / 2));
    int col_start = max(0, static_cast<int>((crop_center.x - tolerance) / resize_factor - crop_size / 2));
    int col_end = min(original_img.cols - 1, static_cast<int>((crop_center.x + tolerance) / resize_factor + crop_size / 2));
    
    // record the location of the upper-left corner of the cropped image
    upper_left_corner = Point(col_start, row_start);
    
    // copy the cropped to a new Mat
    Rect myROI(col_start, row_start, col_end - col_start + 1, row_end - row_start + 1);
    Mat cropped_test_img(original_img, myROI);
    return cropped_test_img;
}