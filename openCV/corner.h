//
//  corner.h
//  openCV
//
//  Created by Tiantong Zhou on 6/21/16.
//  Copyright © 2016 Tiantong Zhou. All rights reserved.
//

#ifndef CORNER_H
#define CORNER_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

/// Function header
//return a vector that contains the positions
std::vector<cv::Point> find_corner_position(std::string,int thresh);
//std::vector<cv::Point> find_corner_position(cv::Mat);
//helper function
std::vector<cv::Point> cornerHarris_demo(int,int thresh,cv::Mat M0);

#endif /* corner_h */