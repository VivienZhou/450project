//
//  main.cpp
//  own_template_matching
//
//  Created by 鲁又佳 on 6/26/16.
//  Copyright (c) 2016 Youjia Lu. All rights reserved.
//

/**
 * @file MatchTemplate_Demo.cpp
 * @brief Sample code to use the function MatchTemplate
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "corner.h"
#include "putative_match.h"
#include "ransac.h"
#include <iostream>
#include <cassert>
#include <cmath>
//#include <stdio.h>

using namespace std;
using namespace cv;

/// Global Variables
Mat img; Mat templ; Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

struct center_and_rotation_t {
    Point center;
    double rotation_angle;
};

/// Function Headers
void MatchingMethod( int, void* );

center_and_rotation_t get_center_and_rotation(vector<double> replacement_mat, Point p1, Point p2);

/**
 * @function main
 */
int main( int, char** argv )
{
    /// Load image and template in grayscale
    img = imread( "/Users/luyoujia/Documents/study_2016Summer/VE450/450project/Data/board/1_image_1.png", 0 );
    templ = imread( "/Users/luyoujia/Documents/study_2016Summer/VE450/450project/Data/board/1_model.png", 0 );
    
    vector<Point> templ_corners = find_corner_position(templ, 190);
    vector<Point> img_corners = find_corner_position(img, 190);
    
    vector<pair<int, int>> putative_matches = get_putative_match(templ_corners, img_corners, templ, img);
    
    
    
    
    
    // testing get_center_and_rotation
    /*
    Point center(1, 1);
    Point upperleft(2, 2);
    vector<double> replacement_mat = {sqrt(2)/2, -sqrt(2)/2, 3, sqrt(2)/2, sqrt(2)/2, 5, 0, 0, 1};
    
    center_and_rotation_t res = get_center_and_rotation(replacement_mat, center, upperleft);
    cout << res.center.x << " " << res.center.y << endl;
    cout << res.rotation_angle << endl;
     */
    
    
    
    /*
    /// Create windows
    namedWindow( image_window, WINDOW_AUTOSIZE );
    namedWindow( result_window, WINDOW_AUTOSIZE );
    
    /// Create Trackbar
    const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );
    
    MatchingMethod( 0, 0 );
    
    waitKey(0);
     */
    return 0;
}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
    /// Source image to display
    Mat img_display;
    img.copyTo( img_display );
    
    /// Create the result matrix
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    
    result.create( result_rows, result_cols, CV_32FC1 );
    
    /// Do the Matching and Normalize
    matchTemplate( img, templ, result, match_method );
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
    
    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;
    
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    
    
    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
    else
    { matchLoc = maxLoc; }
    
    /// Show me what you got
    rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    
    imshow( image_window, img_display );
    imshow( result_window, result );
    
    return;
}

// Input: replacement_mat: a vector with 9 doubles representing a 3*3 transformation matrix; center is the center point of template; upperleft is the upper left point of the template
// Output: a struct containing the center of the matched teplate in the image, and the rotation angle

 center_and_rotation_t get_center_and_rotation(vector<double> replacement_mat, Point center, Point upperleft) {
     assert(replacement_mat.size() == 9);
     double mapped_center_x, mapped_center_y, mapped_upperleft_x, mapped_upperleft_y;
     center_and_rotation_t res;
     
     // do transformation for both center point and upperleft point of the template
     res.center.x = mapped_center_x = replacement_mat[0] * center.x + replacement_mat[1] * center.y + replacement_mat[2];
     res.center.y = mapped_center_y = replacement_mat[3] * center.x + replacement_mat[4] * center.y + replacement_mat[5];
     mapped_upperleft_x = replacement_mat[0] * upperleft.x + replacement_mat[1] * upperleft.y + replacement_mat[2];
     mapped_upperleft_y = replacement_mat[3] * upperleft.x + replacement_mat[4] * upperleft.y + replacement_mat[5];
     
     // x1, y1 are the coordinates of the vector pointing from center to upperleft point of template
     // x2, y2 are the coordinates of the similar vector from the image
     double x1 = upperleft.x - center.x;
     double y1 = upperleft.y - center.y;
     double x2 = mapped_upperleft_x - mapped_center_x;
     double y2 = mapped_upperleft_y - mapped_center_y;
     
     double cos = (x1 * y2 - x2 * y1) / (x1 * x1 + y1 * y1);
     //double sin = (x1 * x2 + y1 * y2) / (x1 * x1 + y1 * y1);
     res.rotation_angle = acos(cos);
 
     return res;
 }

