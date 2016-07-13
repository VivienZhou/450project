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
#include "get_multi_location_and_rotation.h"
#include "annotation.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
    //read image
    Mat templ_img = imread(argv[1], 0);
    Mat test_img = imread(argv[2], 0);

    cout << "begin single object" << endl;
    center_and_angle_t result = get_location_and_rotation(templ_img, test_img, 0, 360, 1);
    cout << "end single object" << endl;


    double threshold = 0.85;
    cout << "begin multiple object" << endl;
    vector<center_and_angle_t> result_vec = get_multi_location_and_rotation(templ_img, test_img, threshold, 0, 360, 5);


    cout << result_vec.size() << endl;
    for (int i = 0; i < result_vec.size(); i ++){
        cout << "Object " << i + 1 << endl;
        cout << "angle: " << result_vec[i].angle << endl;
        cout << "x: " << result_vec[i].center.x << endl;
        cout << "y: " << result_vec[i].center.y << endl;
    }
    cout << "end multiple object" << endl;


    //annotate the image
    //draw_boundary(result, templ_img.cols, templ_img.rows, test_img);

    //waitKey(0);
    return 0;
}

