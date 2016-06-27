#include "putative_match.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>


using namespace cv;
using namespace std;

// This function find putative match using Euclidian distance between two discriptors
// We choose the match with largest distance
// pair.first = temp_corner_id, pair.second = img_corner_id
vector<pair<int, int> > get_putative_match(vector<Point> temp_corner, vector<Point> img_corner, 
                                            const Mat& temp, const Mat& img){
    double threshold = 1.5;
    vector<pair<int, int> > putative_match;
    cout << get_pixel(1,3, img) << endl;
    for (int i = 0; i < img_corner.size(); i ++){
        for (int j = 0; j < temp_corner.size(); j ++){
            double cur_distance = cal_distance(temp_corner[j], temp_corner[i], temp, img);
            // store the pair of match if the distance is smaller than the threshold
            //cout << cur_distance << endl;
            if (cur_distance < threshold){
                putative_match.push_back(make_pair(j, i));
            }
        }
    }
    return putative_match;
}

double cal_distance(Point temp_point, Point img_point, const Mat & temp, const Mat & img){
    double dist = 0;
    for (int i = -2; i <= 2; i ++){
        for (int j = -2; j <= 2; j ++){
            dist += pow((get_pixel(temp_point.x + i, temp_point.y + j, temp) - get_pixel(img_point.x + i, img_point.y + j, img)), 2);
        }
    }
    return dist;
}


double get_pixel(int x, int y, const Mat & img){
    return img.at<float>(x, y);
}






