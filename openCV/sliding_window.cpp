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

const double PI = 3.141592653589793238463;

struct center_and_rotation_t {
    Point center;
    double rotation_angle;
};

// Function Headers

void prepare_img_val(const Mat & image, vector<vector<int> > & img_val);
double cal_similarity(const vector<vector<int> > & templ_val, const vector<vector<int> > & image_val, int row_id, int col_id, double angle);
center_and_rotation_t find_match_pos(const Mat & templ, const Mat & image, int stride, int row_start, int row_end, int col_start, int col_end, double angle_divide_stride, double start_angle, double end_angle);

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
    resize(image, resized_image, Size(), resized_factor, resized_factor, INTER_NEAREST);
    resize(templ, resized_templ, Size(), resized_factor, resized_factor, INTER_NEAREST);

    // start sliding window
    int stride = 1;
    double angle_divide_factor = 0.01;
    
    // rough detection with resized image
    center_and_rotation_t rough_match_pos = find_match_pos(resized_templ, resized_image, stride,
                                    0, resized_image.rows, 
                                    0, resized_image.cols, angle_divide_factor, 0, 2);
    
    /*int x = 241;
    int y = 275;
    double z = 0.05;
    vector<vector<int> > resized_image_val(resized_image.rows, vector<int>(resized_image.cols));
    prepare_img_val(resized_image, resized_image_val);
    vector<vector<int> > resized_templ_val(resized_templ.rows, vector<int>(resized_templ.cols));
    prepare_img_val(resized_templ, resized_templ_val);
    cout<<x/10 + (cos(z) * -1*125 - sin(z) * -1*199)/10<<" "<<y/10 + (sin(z) * -1*125 + cos(z) * -1*199)/10<<endl;
    cout<<cal_similarity(resized_templ_val, resized_image_val, x/10 + (cos(z) * -1*125 - sin(z) * -1*199)/10, y/10 + (sin(z) * -1*125 + cos(z) * -1*199)/10, z)<<endl;
    */
    
    // precise detection with original image
    int tolerance = 1;
    center_and_rotation_t match_pos = find_match_pos(templ, image, stride,
                                    (rough_match_pos.center.y - tolerance) / resized_factor, (rough_match_pos.center.y + tolerance) / resized_factor,
                                    (rough_match_pos.center.x - tolerance) / resized_factor, (rough_match_pos.center.x + tolerance) / resized_factor,
                                    angle_divide_factor, rough_match_pos.rotation_angle - tolerance * angle_divide_factor,
                                    rough_match_pos.rotation_angle
                                     + tolerance * angle_divide_factor);
     
    /*vector<vector<int> > image_val(image.rows, vector<int>(image.cols));
    prepare_img_val(image, image_val);
    vector<vector<int> > templ_val(templ.rows, vector<int>(templ.cols));
    prepare_img_val(templ, templ_val);
    cout<<287 + (cos(3.6) * -1*125 - sin(3.6) * -1*199)<<" "<<352 + (sin(3.6) * -1*125 + cos(3.6) * -1*199)<<endl;
    cout<<cal_similarity(templ_val, image_val, 287 + (cos(3.6) * -1*125 - sin(3.6) * -1*199), 352 + (sin(3.6) * -1*125 + cos(3.6) * -1*199), 3.6)<<endl;*/
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


double cal_similarity(const vector<vector<int> > & templ_val, const vector<vector<int> > & image_val, int row_id, int col_id, double angle){
    int sum_ij = 0; // inner product
    int sum_j2 = 0; // vector length of image
    for (int i = 0; i < templ_val.size(); i ++){
        for (int j = 0; j < templ_val[0].size(); j ++){
            int new_x = (int) (cos(angle) * i - sin(angle) * j) + row_id;
            int new_y = (int) (sin(angle) * i + cos(angle) * j) + col_id;
            int image_pix = 0;
            if (new_x >= 0 && new_y >= 0 && new_x < image_val.size() && new_y < image_val[0].size())
                image_pix = image_val[new_x][new_y];
            //cout<<i<<" "<<j<<" "<<new_x<<" "<<new_y<<" "<<image_pix<<endl;
            int templ_pix = templ_val[i][j];
            sum_ij += templ_pix * image_pix;
            sum_j2 += image_pix * image_pix;
        }
    }
    return sum_ij / sqrt(sum_j2);
}


// row_start is inclusive, row_end is exclusive
center_and_rotation_t find_match_pos(const Mat & templ, const Mat & image, int stride,
                    int row_start, int row_end, int col_start, int col_end, double angle_divide_stride, double start_angle, double end_angle){
    
    // initialize 2D vectors that holds pixel value of the image and template
    vector<vector<int> > image_val(image.rows, vector<int>(image.cols));
    prepare_img_val(image, image_val);
    vector<vector<int> > templ_val(templ.rows, vector<int>(templ.cols));
    prepare_img_val(templ, templ_val);

    double max_similarity = 0;
    //top-left corner
    int best_row = -1;
    int best_col = -1;
    //actual angle = best_angle * PI
    double best_angle = 0;
    for (int i = row_start; i < row_end; i += stride){
        for (int j = col_start; j < col_end; j += stride){
            for (double angle = start_angle; angle <= end_angle; angle += angle_divide_stride){
                
                //cout << "@@@ " << i << " " << j << " " << angle << endl;
                
                double similarity = cal_similarity(templ_val, image_val, i, j, angle * PI);
                if (similarity > max_similarity){
                    max_similarity = similarity;
                    best_row = i;
                    best_col = j;
                    best_angle = angle;
                }
            }
        }
    }
    cout << "similarity score: " << max_similarity << endl;
    int new_x = (int) templ_val.size() / 2;
    int new_y = (int) templ_val[0].size() / 2;
    cout << "row: " << best_row + (int) (cos(best_angle * PI) * new_x - sin(best_angle * PI) * new_y) << endl;
    cout << "column: " << best_col + (int) (sin(best_angle * PI) * new_x + cos(best_angle * PI) * new_y) << endl;
    cout << "angle: " << best_angle * PI << endl;

    center_and_rotation_t result;
    result.center = Point(best_col, best_row);
    result.rotation_angle = best_angle;
    return result;
}









