//
//  main.cpp
//  test
//
//  Created by Yihan Li on 6/10/16.
//  Copyright © 2016 Yihan Li. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "get_location_and_rotation.h"
#include "resize_and_get_location_and_rotation.h"
#include "get_multi_location_and_rotation.h"
#include "get_accurate_center_and_rotation.h"
#include "crop_img.h"
#include "annotation.h"
#include "utility.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
    //read image
    Mat templ_img = imread("/Users/luyoujia/Documents/study_2016Summer/VE450/template/engine_parts/1_model.png", 0);
    Mat test_img = imread("/Users/luyoujia/Documents/study_2016Summer/VE450/template/engine_parts/1_image_8.png", 0);
    //Mat templ_img = imread(argv[1], 0);
    //Mat test_img = imread(argv[2], 0);

    parameter_t para;
    para.resize_factor = 0.2;
    para.threshold = 0.6;
    para.nearby_size = 9;

    //center_and_angle_t result = resize_and_get_location_and_rotation(templ_img, test_img);

    Mat resized_test_img, resized_templ_img;
    resize(test_img, resized_test_img, Size(), para.resize_factor, para.resize_factor, INTER_NEAREST);
    resize(templ_img, resized_templ_img, Size(), para.resize_factor, para.resize_factor, INTER_NEAREST);
    
    //double threshold = 0.6;
    vector<center_and_angle_t> rough_centers_and_angles = get_multi_location_and_rotation(resized_templ_img, resized_test_img, para.nearby_size, para.threshold, 0, 360, 5);
    
    int result_num = static_cast<int>(rough_centers_and_angles.size());
    double crop_size = sqrt(templ_img.cols * templ_img.cols + templ_img.rows * templ_img.rows);
    
    // a vector storing final results
    vector<center_and_angle_t> result_centers_and_angles;
    
    for (int i = 0; i < result_num; ++i) {
        Point upper_left_corner;
        Mat cropped_img = crop_img(test_img, upper_left_corner, crop_size, rough_centers_and_angles[i].center, para.resize_factor);
        // error checking, if cropped_img is smaller than templ_img, ignore this point
        double min_side = min(cropped_img.rows, cropped_img.cols);
        if (min_side < templ_img.rows || min_side < templ_img.cols) {
            continue;
        }
        center_and_angle_t result = get_accurate_center_and_angle(cropped_img, templ_img, upper_left_corner, rough_centers_and_angles[i].angle);
        result_centers_and_angles.push_back(result);
    }
    
    // calculate the rotation angle and center location in the resized test image
    // center_and_angle_t resized_center_and_angle = get_location_and_rotation(resized_templ_img, resized_test_img);
    
    
    // calculate the rotation angle and center location in the resized test image
    //center_and_angle_t resized_center_and_angle = get_location_and_rotation(resized_templ_img, resized_test_img);

    //annotate the image
    draw_boundary(result_centers_and_angles, templ_img.cols, templ_img.rows, test_img);

    waitKey(0);
    return 0;
}

