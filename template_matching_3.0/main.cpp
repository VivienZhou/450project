//
//  main.cpp
//  test
//
//  Created by Yihan Li on 6/10/16.
//  Copyright © 2016 Yihan Li. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "get_location_and_rotation.h"
#include "annotation.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
    //read image
    // Mat templ_img = imread("/Users/liyihan/Downloads/pack/test/board/1_model.png", 0);
    // Mat test_img = imread("/Users/liyihan/Downloads/pack/test/board/1_image_1.png", 0);

    Mat templ_img = imread(argv[1], 0);
    Mat test_img = imread(argv[2], 0);
    center_and_angle_t result = get_location_and_rotation(templ_img, test_img, 0, 360, 1);

    //annotate the image
    draw_boundary(result, templ_img.cols, templ_img.rows, test_img);

    waitKey(0);
    return 0;
}

