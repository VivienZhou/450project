//
//  ransac.h
//  test
//
//  Created by Yihan Li on 6/26/16.
//  Copyright © 2016 Yihan Li. All rights reserved.
//

#ifndef ransac_h
#define ransac_h
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

/// Function header
//return a transform matrix
std::double ransac(std::vector<cv::Point>, std::vector<cv::Point>, std::vector<pair<int, int>>);

#endif /* ransac_h */
