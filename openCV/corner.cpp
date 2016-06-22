#include "corner.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>


using namespace cv;
using namespace std;

/// Global variables
Mat src, src_gray, temp;
vector<Point> corner_position;
int thresh = 190;
int max_thresh = 255;

std::string source_window = "Source image";
std::string corners_window = "Corners detected";



std::vector<cv::Point> find_corner_position(){
    /// Load source image and convert it to gray
    //hard code
    src = imread("/Users/Haitian/Documents/CurrentSemester/VE450/450project/Data/board/1_model.png", 1);
    //src = imread("/Users/zhou/Documents/VE450/image/board/1_image_5.png", 1 );
    
    cvtColor(src, src_gray, CV_BGR2GRAY);
    
    //corners record the positions of corners
    //vector<Point> corners;
    
    /// Create a window and a trackbar
    namedWindow(source_window, CV_WINDOW_AUTOSIZE);
    createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
    imshow(source_window, src);
    
    //corners record positions
    cornerHarris_demo(0, &corner_position);
    
    //wait for such time
    waitKey(10000);
    return corner_position;
}



/** @function cornerHarris_demo */
void cornerHarris_demo(int, void*){
    corner_position.clear();
    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros(src.size(), CV_32FC1);
    
    /// Detector parameters
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
    
    /// Detecting corners
    cornerHarris(src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
    
    /// Normalizing
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);
    
    /// Drawing a circle around corners
    for(int j = 0; j < dst_norm.rows; j++){
        for(int i = 0; i < dst_norm.cols; i++){
            if((int) dst_norm.at<float>(j, i) > thresh){
                corner_position.push_back(Point{j, i});
                circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
            }
        }
    }
    /// Showing the result
    namedWindow(corners_window, CV_WINDOW_AUTOSIZE);
    imshow(corners_window, dst_norm_scaled);
    
    //hard code, save image
    imwrite("/Users/Haitian/Documents/CurrentSemester/VE450/450project/Data/200_temp.jpg", dst_norm_scaled);
}
