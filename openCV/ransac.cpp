//
//  ransac.cpp
//  test
//
//  Created by Yihan Li on 6/26/16.
//  Copyright © 2016 Yihan Li. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "corner.h"
#include <iostream>
#include <string>
#include <time.h>


using namespace std;
using namespace cv;

int point_dist(cv::Point p1, cv::Point p2){
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

std::vector<double> ransac(std::vector<cv::Point> temp_corners, std::vector<cv::Point> test_corners, std::vector<pair<int, int>> match_list){
    srand (time(NULL));
    
    //const
    int ransac_iter_times = 1000;
    
    std::vector<double> transform_matrix;
    transform_matrix.resize(4);
    int match_num = (int)match_list.size();
    int lucky_x;
    int lucky_y;
    int max_match_num = 0;
    
    for (int ransac_iter = 0; ransac_iter < ransac_iter_times; ransac_iter++){
        lucky_x = rand() % match_num;
        lucky_y = rand() % match_num;
        while (lucky_y == lucky_x)
            lucky_y = rand() % match_num;
        cv::Point temp_p1 = temp_corners[match_list[lucky_x].first];
        cv::Point temp_p2 = temp_corners[match_list[lucky_y].first];
        cv::Point test_p1 = temp_corners[match_list[lucky_x].second];
        cv::Point test_p2 = temp_corners[match_list[lucky_y].second];
        //check distance
        if (abs(point_dist(temp_p1, test_p1) - point_dist(temp_p2, test_p2)) > 20)
            continue;
        int a1 = temp_p1.x;
        int a2 = temp_p1.y;
        int b1 = temp_p2.x;
        int b2 = temp_p2.y;
        int c1 = test_p1.x;
        int c2 = test_p1.y;
        int d1 = test_p2.x;
        int d2 = test_p2.y;
        double w;
        double x;
        double y;
        double z;
        if (a1 == b1 && a2 == b2)
            continue;
        if (a2 == b2){
            x = (double)(c2-d2)/(a1-b1);
            w = (double)(c1-d1)/(a1-b1);
        }
        else if (a1 == b1){
            x = (double)(c1-d1)/(b2-a2);
            w = (double)(c2-d2)/(a2-b2);
        }
        else {
            w = ((double)(c1-d1)/(a2-b2)+(double)(c2-d2)/(a1-b1))/((double)(a2-b2)/(a1-b1)+(double)(a1-b1)/(a2-b2));
            x = ((a1-b1)*w-c1+d1)/(a2-b2);
        }
        y = c1-a1*w+a2*x;
        z = c2-a1*x-a2*w;
        
        int correct_match_num = 0;
        for (int i = 0; i < match_num; i++){
            a1 = temp_corners[match_list[i].first].x;
            a2 = temp_corners[match_list[i].first].y;
            b1 = temp_corners[match_list[i].second].x;
            b2 = temp_corners[match_list[i].second].y;
            double delta;
            delta = a1*w-x*a2+y-b1+a1*x+a2*w+z-b1;
            if (delta<10)
                correct_match_num++;
        }
        if (correct_match_num > max_match_num){
            max_match_num = correct_match_num;
            transform_matrix[0] = w;
            transform_matrix[1] = x;
            transform_matrix[2] = y;
            transform_matrix[3] = z;
        }
    }
    
    return transform_matrix;
}