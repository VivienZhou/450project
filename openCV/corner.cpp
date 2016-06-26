#include "corner.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables

//vector<Point> corner_position;

//int max_thresh = 255;

std::string source_window = "Source image";
std::string corners_window = "Corners detected";



std::vector<cv::Point> find_corner_position(string file_name, int thresh){
    /// Load source image and convert it to gray
    //hard code
    //vector<Point> corner_position
    Mat src_gray;
    Mat dst_orign, dst_norm_origin, dst_norm_scaled_origin;
    src_gray = imread( file_name, 0 );
    //src = imread("/Users/zhou/Documents/VE450/image/board/1_model.png", 1);
    //src = imread("/Users/zhou/Documents/VE450/image/board/1_image_5.png", 1 );
    
    Scalar     mean;
    Scalar     stddev;
    cv::meanStdDev ( src_gray, mean, stddev );
    uchar       mean_pxl = mean.val[0];
    uchar       stddev_pxl = stddev.val[0];
    //cvtColor(src, src_gray, CV_BGR2GRAY);
    uchar *input = (uchar*)(src_gray.data);
//    //cout << input.end()<<endl;
    //cout << int(input[0] - mean_pxl)<<endl;
    int row = src_gray.rows;
    int col = src_gray.cols;
    
    //Mat M0;
    Mat M0(row,col,CV_32F);
    
//    double mean = 0.0;
//    double std = 0.0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            M0.at<float>(i,j) = float(input[i*col + j] - mean_pxl) / float(stddev_pxl);
        }
    }

    //src_gray = src_gray / std;
    /// Create a window and a trackbar
    namedWindow(source_window, CV_WINDOW_AUTOSIZE);
    //createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
    imshow(source_window, src_gray);
    
    //corners record positions
    return cornerHarris_demo(0,thresh,M0);
    
    //wait for such time
    //return corner_position;
}



/** @function cornerHarris_demo */
vector<Point> cornerHarris_demo(int, int thresh,Mat M0){
    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros(M0.size(), CV_32FC1);
    vector<Point> corner_position;
    /// Detector parameters
    int blockSize = 4;
    int apertureSize = 7;
    double k = 0.1;
    
    /// Detecting corners

    
    
    
    
    
    cornerHarris(M0, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
    
    /// Normalizing
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);
    /// Drawing a circle around corners
    for(int j = 0; j < dst_norm.rows; j++){
        for(int i = 0; i < dst_norm.cols; i++){
            //cout<<"row: "<<j<<" col: "<<i<<endl;
            if((int) dst_norm.at<float>(j, i) > thresh){
                //cout<<"row: "<<j<<" col: "<<i<<endl;
                corner_position.push_back(Point{j, i});
                circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
            }
        }
    }
    cout<<corner_position.size()<<endl;
    /// Showing the result
    namedWindow(corners_window, CV_WINDOW_AUTOSIZE);
    imshow(corners_window, dst_norm_scaled);
    
    //hard code, save image
    imwrite("/Users/huangtianhao1130/450project/pack/test/board/200_temp.jpg", dst_norm_scaled);
    return corner_position;
}