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
Point find_match_pos(const Mat & templ, const Mat & image, int stride, int row_start, int row_end, int col_start, int col_end);

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


    // resize image and templ
    double resized_factor = 0.1;
    Mat resized_image, resized_templ;
    resize(image, resized_image, Size(), resized_factor, resized_factor);
    resize(templ, resized_templ, Size(), resized_factor, resized_factor);

    // start sliding window
    int stride = 1;
    
    // rough detection with resized image
    Point rough_match_pos = find_match_pos(resized_templ, resized_image, stride, 
                                    0, resized_image.rows - resized_templ.rows + 1, 
                                    0, resized_image.cols - resized_templ.cols + 1);

    // precise detection with original image
    int tolerance = 1;
    Point match_pos = find_match_pos(templ, image, stride,
                                    (rough_match_pos.y - tolerance) / resized_factor, (rough_match_pos.y + tolerance) / resized_factor,
                                    (rough_match_pos.x - tolerance) / resized_factor, (rough_match_pos.x + tolerance) / resized_factor);
                                            
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


// row_start is inclusive, row_end is exclusive
Point find_match_pos(const Mat & templ, const Mat & image, int stride, 
                    int row_start, int row_end, int col_start, int col_end){
    
    // initialize 2D vectors that holds pixel value of the image and template
    vector<vector<int> > image_val(image.rows, vector<int>(image.cols));
    prepare_img_val(image, image_val);
    vector<vector<int> > templ_val(templ.rows, vector<int>(templ.cols));
    prepare_img_val(templ, templ_val);

    double max_similarity = 0;
    int best_row = -1;
    int best_col = -1;
    for (int i = row_start; i < row_end; i += stride){
        for (int j = col_start; j < col_end; j += stride){
            double similarity = cal_similarity(templ_val, image_val, i, j);
            if (similarity > max_similarity){
                max_similarity = similarity;
                best_row = i;
                best_col = j;
                
            }
        }
    }
    cout << "similarity score: " << max_similarity << endl;
    cout << "row: " << best_row + templ_val.size() / 2 << endl;
    cout << "column: " << best_col + templ_val[0].size() / 2 << endl;

    return Point(best_col, best_row);
}









