//
//  sliding_window.cpp
//  own_template_matching
//
//  Created by Haitian Sun on 6/30/16.
//  Copyright (c) 2016 Haitian Sun. All rights reserved.
//


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;


struct center_and_rotation_t {
    Point center;
    double rotation_angle;
};

// Function Headers

void prepare_img_val(const Mat & image, vector<vector<int> > & img_val);
double cal_similarity(const vector<vector<int> > & templ_val, const vector<vector<int> > & image_val, int row_id, int col_id);

/**
 * @function main
 */
int main( int argc, char** argv ){
    if( argc != 3) {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat templ = imread(argv[1], 0); // 0 indicated grayscale
    Mat image = imread(argv[2], 0);

    // Check for invalid input
    if(! image.data ) {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    if(! templ.data ) {
        cout <<  "Could not open or find the template" << std::endl ;
        return -1;
    }

    //Scalar intensity = image.at<uchar>(Point(645, 491));
    //int pix_val = intensity.val[0];
    //cout <<  pix_val << endl;

    // initialize 2D vectors that holds pixel value of the image and template
    vector<vector<int> > image_val(image.rows, vector<int>(image.cols));
    prepare_img_val(image, image_val);
    vector<vector<int> > templ_val(templ.rows, vector<int>(templ.cols));
    prepare_img_val(templ, templ_val);

    // start sliding window
    int stride = 3;
    double max_similarity = 0;
    int best_row = -1;
    int best_col = -1;
    for (int i = 0; i <= image.rows - templ.rows; i += stride){
        for (int j = 0; j <= image.cols - templ.cols; j += stride){
            // calculate similarity
            //cout << i << " " << j << endl;
            double similarity = cal_similarity(templ_val, image_val, i, j);
            //cout << i << " " << j << endl;
            if (similarity > max_similarity){
                max_similarity = similarity;
                best_row = i;
                best_col = j;
                cout << max_similarity << " " << i << " " << j << endl;
            }
        }
    }
    cout << max_similarity << endl;
    cout << best_row + image.rows / 2 << endl;
    cout << best_col + image.cols / 2 << endl;

    // Create a window for display.
    //namedWindow( "Display window", WINDOW_AUTOSIZE );
    //imshow( "Display window", image );                  

    // Wait for a keystroke in the window
    //waitKey(0);                                          
    return 0;
}




void prepare_img_val(const Mat & image, vector<vector<int> > & img_val){
    for (int i = 0; i < image.rows; i ++){
        for (int j = 0; j < image.cols; j ++){
            Scalar intensity = image.at<uchar>(i, j);
            img_val[i][j] = intensity[0];
        }
    }
    return;
}


double cal_similarity(const vector<vector<int> > & templ_val, const vector<vector<int> > & image_val, int row_id, int col_id){
    int sum_ij = 0; // inner product
    int sum_j2 = 0; // vector length of image
    for (int i = 0; i < templ_val.size(); i ++){
        for (int j = 0; j < templ_val[0].size(); j ++){
            int image_pix = image_val[i + row_id][j + col_id];
            int templ_pix = templ_val[i][j];
            sum_ij += templ_pix * image_pix;
            sum_j2 += image_pix * image_pix;
        }
    }
    return sum_ij / sqrt(sum_j2);
}











