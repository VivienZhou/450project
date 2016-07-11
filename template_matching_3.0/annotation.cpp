
#include "annotation.h"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;
using namespace cv;


void draw_boundary(const center_and_angle_t& object_info, int scaleCol, int scaleRow, Mat& test_img){
    double coord[2][5] = {{- scaleCol/2.0, scaleCol/2.0, scaleCol/2.0, - scaleCol/2.0, - scaleCol/2.0},
        {- scaleRow/2.0, - scaleRow/2.0, scaleRow/2.0, scaleRow/2.0, - scaleRow/2.0}};
    
    double alpha = -object_info.angle;
    double cos_alpha = cos(alpha);
    double sin_alpha = sin(alpha);
    double rotation_para[2][2] = {{cos_alpha, -sin_alpha}, {sin_alpha, cos_alpha}};
    
    double rotatedCoord[2][5]; // = [cos(alpha), -sin(alpha); sin(alpha), cos(alpha)] * coord;
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 5; ++j){
            rotatedCoord[i][j] = rotation_para[i][0] * coord[0][j] + rotation_para[i][1] * coord[1][j];
        }
    }
    
    Point pt1(rotatedCoord[0][0] + object_info.center.x, rotatedCoord[1][0] + object_info.center.y);
    Point pt2(rotatedCoord[0][1] + object_info.center.x, rotatedCoord[1][1] + object_info.center.y);
    Point pt3(rotatedCoord[0][2] + object_info.center.x, rotatedCoord[1][2] + object_info.center.y);
    Point pt4(rotatedCoord[0][3] + object_info.center.x, rotatedCoord[1][3] + object_info.center.y);
    Point pt5(rotatedCoord[0][4] + object_info.center.x, rotatedCoord[1][4] + object_info.center.y);
    
    //draw 4 lines
    cvtColor(test_img, test_img, CV_GRAY2BGR);
    line(test_img, pt1, pt2, cv::Scalar(0, 0, 255), 2, 8, 0);
    line(test_img, pt2, pt3, cv::Scalar(0, 0, 255), 2, 8, 0);
    line(test_img, pt3, pt4, cv::Scalar(0, 0, 255), 2, 8, 0);
    line(test_img, pt4, pt5, cv::Scalar(0, 0, 255), 2, 8, 0);
    imshow( "annotation", test_img);
}
