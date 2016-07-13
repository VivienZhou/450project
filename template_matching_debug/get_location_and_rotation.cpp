//
//  get_location_and_rotation.cpp
//  own_template_matching
//
//  Created by 鲁又佳 on 7/11/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

#include "get_location_and_rotation.h"

using namespace std;
using namespace cv;
//===============================================
center_and_angle_t cal_original_coordinate(int rotated_image_rows, int rotated_image_cols,
                                           int image_rows, int image_cols,
                                           int rotated_coord_row, int rotated_coord_col,
                                           double rotation_angle){
    // angle is in radians
    double original_angle = -rotation_angle;
    while (original_angle < 0)
        original_angle += PI * 2;
    cout << "Angle: " << original_angle << endl;
    
    double original_coord_col = (rotated_coord_col - rotated_image_cols / 2) * cos(-rotation_angle) - (rotated_image_rows / 2 - rotated_coord_row) * sin(-rotation_angle) + image_cols / 2;
    
    double original_coord_row = -((rotated_coord_col - rotated_image_cols / 2) * sin(-rotation_angle) + (rotated_image_rows / 2 - rotated_coord_row) * cos(-rotation_angle)) + image_rows / 2;
    
    cout << "cols (x): " << original_coord_col << endl;
    cout << "rows (y): " << original_coord_row << endl;
    
    center_and_angle_t res;
    res.center = Point(original_coord_col, original_coord_row);
    res.angle = original_angle;
    return res;
    
}

//===============================================
Mat rotate_and_crop(const cv::Mat &test_img, double angle, const cv::Rect &ROI, bool is_int) {
    Mat test_rotate_img;
    
    //template matching
    Point center;
    double scale = 1;
    
    Mat rot_mat(2, 3, CV_32FC1);
    Size dsize = test_img.size();

    int test_cols = test_img.cols;
    int test_rows = test_img.rows;
    dsize.width = sqrt(test_cols * test_cols + test_rows * test_rows);
    dsize.height = dsize.width;
    center = Point(dsize.width/2, dsize.height/2);
    int row_start = dsize.height / 2 - test_rows / 2;
    int col_start = dsize.width / 2 - test_cols / 2;
    
    imshow("12", test_img);
    //fill with test image
    Mat new_test_img;
    if (is_int)
        new_test_img = Mat::zeros(dsize.height, dsize.width, CV_8U);
    else
        new_test_img = Mat::zeros(dsize.height, dsize.width, CV_32FC1);
    //new_test_img.create(dsize.height, dsize.width, 0);
    test_img.copyTo(new_test_img.rowRange(row_start, row_start + test_rows).colRange(col_start, col_start + test_cols));
    
    //rotate
    imshow("123", new_test_img);
    rot_mat = getRotationMatrix2D(center, angle, scale);
    warpAffine(new_test_img, test_rotate_img, rot_mat, dsize);
    imshow("1234", test_rotate_img);
    //crop
    //osize.width = abs(test_img.cols * cos(angle/180*PI)) + abs(test_img.rows * sin(angle/180*PI));
    //osize.height = abs(test_img.cols * sin(angle/180*PI)) + abs(test_img.rows * cos(angle/180*PI));
    //Rect myROI(dsize.width/2-osize.width/2, dsize.height/2-osize.height/2, osize.width, osize.height);
    Mat new_test_rotate_img(test_rotate_img, ROI);
    return new_test_rotate_img;
}

//===============================================
Mat cal_similarity_score(const cv::Mat &templ_img, const cv::Mat &test_img, double angle) {
    Mat result;
    int result_cols;
    int result_rows;
    Size dsize = test_img.size();
    Size osize = test_img.size();
    osize.width = abs(test_img.cols * cos(angle/180*PI)) + abs(test_img.rows * sin(angle/180*PI));
    osize.height = abs(test_img.cols * sin(angle/180*PI)) + abs(test_img.rows * cos(angle/180*PI));
    
    int test_cols = test_img.cols;
    int test_rows = test_img.rows;
    dsize.width = sqrt(test_cols * test_cols + test_rows * test_rows);
    dsize.height = dsize.width;

    Rect myROI(dsize.width/2-osize.width/2, dsize.height/2-osize.height/2, osize.width, osize.height);
    Mat new_test_rotate_img = rotate_and_crop(test_img, angle, myROI);
    result_cols =  new_test_rotate_img.cols - templ_img.cols + 1;
    result_rows = new_test_rotate_img.rows - templ_img.rows + 1;
    result.create(result_rows, result_cols, CV_32FC1);
    matchTemplate(new_test_rotate_img, templ_img, result, CV_TM_CCORR_NORMED);

    return result;
}

//===============================================
center_and_angle_t get_location_and_rotation(const cv::Mat &templ_img, const cv::Mat &test_img, double rotation_start, double rotation_end, double rotation_stride) {
    //read image

    Mat test_rotate_img;
    Mat result;
    
    Point best_loc;
    double best_angle = 0;
    double best_val = 0;
    int best_rows = 0;
    int best_cols = 0;
    double min_val;
    double max_val;
    Point min_loc;
    Point max_loc;
    Size osize = test_img.size();
    int test_cols = test_img.cols;
    int test_rows = test_img.rows;
    
    for (double angle = rotation_start; angle < rotation_end; angle += rotation_stride * 10) {
        
        result = cal_similarity_score(templ_img, test_img, angle);
        osize.width = abs(test_img.cols * cos(angle/180*PI)) + abs(test_img.rows * sin(angle/180*PI));
        osize.height = abs(test_img.cols * sin(angle/180*PI)) + abs(test_img.rows * cos(angle/180*PI));
        /// Localizing the best match with minMaxLoc
        /// max_loc here is the matching point
        minMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc, Mat());

        if (max_val > best_val) {
            best_val = max_val;
            best_angle = angle;
            best_loc.x = max_loc.x + templ_img.cols / 2;
            best_loc.y = max_loc.y + templ_img.rows / 2;
            best_cols = osize.width;
            best_rows = osize.height;
        }
        
    }
    
    double rough_angle = best_angle;
    
    for (double angle = rough_angle - 5; angle < rough_angle + 6; angle += rotation_stride) {
        
        result = cal_similarity_score(templ_img, test_img, angle);
        osize.width = abs(test_img.cols * cos(angle/180*PI)) + abs(test_img.rows * sin(angle/180*PI));
        osize.height = abs(test_img.cols * sin(angle/180*PI)) + abs(test_img.rows * cos(angle/180*PI));
        
        /// Localizing the best match with minMaxLoc
        /// max_loc here is the matching point
        minMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc, Mat());
        
        if (max_val > best_val) {
            best_val = max_val;
            best_angle = angle;
            best_loc.x = max_loc.x + templ_img.cols / 2;
            best_loc.y = max_loc.y + templ_img.rows / 2;
            best_cols = osize.width;
            best_rows = osize.height;
        }
        
    }
    
    return cal_original_coordinate(best_rows, best_cols,
                                   test_rows, test_cols,
                                   best_loc.y, best_loc.x,
                                   best_angle / 180 * PI);
    
}

