//
//  find_object.cpp
//  test
//
//  Created by 黄 天豪 on 16/7/11.
//  Copyright © 2016年 Tianhao Huang. All rights reserved.
//

#include "find_object.h"
#include "get_location_and_rotation.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
using namespace cv;

bool is_highest(int row, int col, int nearby_size, Mat value){
    for(int i = row - nearby_size / 2; i <= row + nearby_size / 2; i++){
        for(int j = col - nearby_size / 2; j <= col + nearby_size / 2; j++){
            if(value.at<float>(row,col) < value.at<float>(i,j)){
                return false;
            }
        }
    }
    return true;
}

vector<center_and_angle_t> find_object(Mat value, Mat angle, int nearby_size, double threshold){
    vector<center_and_angle_t> objects;
    
    if(double(nearby_size) / 2 == nearby_size / 2){
        cout<<"Please input a odd number as nearby size"<<endl;
        return objects;
    }
    
    for(int i = nearby_size / 2; i < value.rows - nearby_size / 2; i++){
        for(int j = nearby_size / 2; j < value.cols - nearby_size / 2; j++){
            if(value.at<float>(i, j) < threshold){
                continue;
            }
            //cout << value.at<float>(i, j) << endl;
            if(is_highest(i, j, nearby_size, value) == true){
                value.at<float>(i, j) = value.at<float>(i, j) + 256;
                struct center_and_angle_t object;
                object.center = Point(j,i);
                object.angle = (360 - angle.at<float>(i,j)) / 180 * 3.1416;
                objects.push_back(object);
            }
        }
        
    }
   
    return objects;
}




