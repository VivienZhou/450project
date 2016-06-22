//
//  main.cpp
//  test
//
//  Created by Yihan Li on 6/10/16.
//  Copyright © 2016 Yihan Li. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/// 全局变量
Mat img; Mat templ; Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

/// 函数声明
void MatchingMethod( int, void* );



int main( int argc, char** argv )
{
    //  读图片
    img = imread( "/Users/Haitian/Documents/CurrentSemester/VE450/450project/Data/board/1_image_5.png", 1 );
    templ = imread( "/Users/Haitian/Documents/CurrentSemester/VE450/450project/Data/board/1_model.png", 1 );
    
    //  创建图像显示窗口
    namedWindow( image_window, CV_WINDOW_AUTOSIZE );
    namedWindow( result_window, CV_WINDOW_AUTOSIZE );
    
    //  创建混动条
    char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );
    
    MatchingMethod( 0, 0 );
    
    waitKey(0);
    return 0;
}



// 模板匹配
void MatchingMethod( int, void* )
{
    // 用于显示结果
    Mat img_display;
    img.copyTo( img_display );
    
    // 用于存储匹配结果的矩阵
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    result.create( result_cols, result_rows, CV_32FC1 );
    
    // 进行模板匹配
    matchTemplate( img, templ, result, match_method );
    // 归一化结果（方便显示结果）
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
    
    // 找到最佳匹配位置
    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;
    
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );   // 寻找result中的最大和最小值，以及它们所处的像素位置
    
    // 使用SQDIFF和SQDIFF_NORMED方法时：值越小代表越相似
    // 使用其他方法时：值越大代表越相似
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    {
        matchLoc = minLoc;
    }
    else
    {
        matchLoc = maxLoc;
    }
    
    // 显示匹配结果
    rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    
    imshow( image_window, img_display );
    imshow( result_window, result );
}
