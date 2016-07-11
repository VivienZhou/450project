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
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

/*double PI = 3.14159265359;

void cal_original_coordinate(int rotated_image_rows, int rotated_image_cols,
                             int image_rows, int image_cols,
                             int rotated_coord_row, int rotated_coord_col,
                             double rotation_angle){
    // angle is in radians
    double original_angle = -rotation_angle;
    while (original_angle < 0)
        original_angle += PI * 2;
    cout << "Angle: " << original_angle << endl;
    //double rotate_back_angle = atan((rotated_image_rows / 2 - rotated_coord_row) / (rotated_coord_col - rotated_image_cols / 2)) - rotation_angle;
    
    double original_coord_col = (rotated_coord_col - rotated_image_cols / 2) * cos(-rotation_angle) - (rotated_image_rows / 2 - rotated_coord_row) * sin(-rotation_angle) + image_cols / 2;
    
    double original_coord_row = -((rotated_coord_col - rotated_image_cols / 2) * sin(-rotation_angle) + (rotated_image_rows / 2 - rotated_coord_row) * cos(-rotation_angle)) + image_rows / 2;
    
    cout << "cols (x): " << original_coord_col << endl;
    cout << "rows (y): " << original_coord_row << endl;
    
}*/

int main( int argc, char** argv )
{
    //read image
    center_and_angle_t result = get_location_and_rotation("/Users/luyoujia/Documents/study_2016Summer/VE450/template/board/1_model.png", "/Users/luyoujia/Documents/study_2016Summer/VE450/template/board/1_image_1.png", 0, 360, 1);
    
    
    string file_name = "/Users/luyoujia/Documents/study_2016Summer/VE450/template/board/1_model.png";
    Mat templ_img = imread(file_name, 0);
    file_name = "/Users/luyoujia/Documents/study_2016Summer/VE450/template/board/1_image_1.png";
    /*Mat test_img = imread(file_name, 0);
    Mat test_rotate_img;
    Mat result;
    
    //template matching
    Point center;
    double scale = 1;
    Point best_loc;
    double best_angle = 0;
    double best_val = 0;
    double delta_angle = 1;
    int best_rows = 0;
    int best_cols = 0;
    double min_val;
    double max_val;
    Point min_loc;
    Point max_loc;
    Mat rot_mat(2, 3, CV_32FC1);
    Size dsize = test_img.size();
    Size osize = test_img.size();
    int result_cols;
    int result_rows;
    int test_cols = test_img.cols;
    int test_rows = test_img.rows;
    dsize.width = sqrt(test_cols * test_cols + test_rows * test_rows);
    dsize.height = dsize.width;
    center = Point(dsize.width/2, dsize.height/2);
    int row_start = dsize.height / 2 - test_rows / 2;
    int col_start = dsize.width / 2 - test_cols / 2;

    for (double angle = 0; angle < 360; angle += delta_angle)
    {
        //dsize.width = abs(test_img.cols * cos(angle/180*PI)) + abs(test_img.rows * sin(angle/180*PI));
        //dsize.height = abs(test_img.cols * sin(angle/180*PI)) + abs(test_img.rows * cos(angle/180*PI));

        
        //fill with test image
        Mat new_test_img;
        new_test_img.create(dsize.height, dsize.width, 0);
        test_img.copyTo(new_test_img.rowRange(row_start, row_start + test_rows).colRange(col_start, col_start + test_cols));
        
        //rotate
        rot_mat = getRotationMatrix2D(center, angle, scale);
        warpAffine(new_test_img, test_rotate_img, rot_mat, dsize);
    
        //crop
        osize.width = abs(test_img.cols * cos(angle/180*PI)) + abs(test_img.rows * sin(angle/180*PI));
        osize.height = abs(test_img.cols * sin(angle/180*PI)) + abs(test_img.rows * cos(angle/180*PI));
        Rect myROI(dsize.width/2-osize.width/2, dsize.height/2-osize.height/2, osize.width, osize.height);
        Mat new_test_rotate_img(test_rotate_img, myROI);
        
        //imshow("123", new_test_rotate_img);
        
        result_cols =  new_test_rotate_img.cols - templ_img.cols + 1;
        result_rows = new_test_rotate_img.rows - templ_img.rows + 1;
        result.create(result_rows, result_cols, CV_32FC1);
        matchTemplate(new_test_rotate_img, templ_img, result, CV_TM_CCORR_NORMED);
    
        minMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc, Mat());
        rectangle( new_test_rotate_img, max_loc, Point( max_loc.x + templ_img.cols , max_loc.y + templ_img.rows ), Scalar::all(0), 2, 8, 0 );
        
        //imshow( "1234", new_test_rotate_img);

        /// Localizing the best match with minMaxLoc
        /// max_loc here is the matching point
        minMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc, Mat());
        if (max_val > best_val)
        {
            best_val = max_val;
            best_angle = angle;
            best_loc.x = max_loc.x + templ_img.cols / 2;
            best_loc.y = max_loc.y + templ_img.rows / 2;
            best_cols = osize.width;
            best_rows = osize.height;
        }
        
    }
    cal_original_coordinate(best_rows, best_cols,
                            test_rows, test_cols,
                            best_loc.y, best_loc.x,
                            best_angle / 180 * PI);
    
    
    
    waitKey(0);*/
    return 0;
}

