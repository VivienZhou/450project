//
//  putative_match.h
//  openCV
//
//  Created by Haitian SUN on 6/26/16.
//  Copyright © 2016 Tiantong Zhou. All rights reserved.
//

#ifndef putative_match_h
#define putative_match_h

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <pair>
using namespace std;
using namespace cv;

/// Function header
//return a vector that contains putative matches
vector<pair<int, int>> get_putative_match(vector<Point> temp_corner, vector<Point> img_corner, const Mat& temp, const Mat& img);

// helper function
// Calculate distance between two discriptors. The center point of the discriptor is given as parameter
double cal_distance(Point temp_point, Point img_point, const Mat & temp, const Mat & img);

double get_pixel(int x, int y, const Mat & img);

#endif /* putative_match_h */
