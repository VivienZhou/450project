#include "frame.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
using namespace cv;

// Input: length and width of the window, center of the window in the image
// Output: Matrix of the extracted window
Mat get_window_mat(int length, int width, Point loc, const Mat& image_mat);

// Given two matrices, get the unnormed cosine similarity of the two matrices
double correlation(Mat template_mat, Mat img_window_mat);

// Given two matrices, get the cosine similarity of the two matrices
double correlation_normed(Mat template_mat, Mat img_window_mat);

// Given two matrices, get the square difference of the two matrices
double square_diff(Mat template_mat, Mat img_window_mat);

// Given two matrices, get the normed square difference of the two matrices
double square_diff_normed(Mat template_mat, Mat img_window_mat);

// Input: template matrix and window matrix in the image.
// For the two given matrices, subtract an average pixel value
// from each pixel and get two deviation matrices Then do the dot product of the
// two deviation matrices,
// output is the dot product of the deviation matrices
double coefficient(Mat template_mat, Mat img_window_mat);

// Input: template matrix and window matrix in the image.
// For the two given matrices, subtract an average pixel value
// from each pixel and get two deviation matrices Then do the dot product of the
// two deviation matrices,
// output is the cosine similarity of the deviation matrices
double coefficient_normed(Mat template_mat, Mat img_window_mat);

// method_map maps string of method name to function pointer that calculates
// corresponding similarity score.
using Method_map_t = map<string, double(*)(Mat, Mat)>;
Method_map_t method_map = map<string, double(*)(Mat, Mat)> {
    {"correlation", &correlation},
    {"correlation_normed", &correlation_normed},
    {"square_diff", &square_diff},
    {"square_diff_normed", &square_diff_normed},
    {"coefficient", &coefficient},
    {"coefficient_normed", &coefficient_normed}
};

// Given method_name and two matrices, calculate the similarity score of the corresponding method
double similarity_score(string sim_method_name, Mat template_mat, Mat img_window_mat) {
    return method_map[sim_method_name](template_mat, img_window_mat);
}

// Input: template matrix, original image matrix, threshold value
// Usage: calculate similaritis of all locations
// Output: a vector of all the matching locations higher than the threshold
vector<Point> get_locations_sliding_window(Mat template_mat, Mat image_mat, string sim_method_name, double threshold) {
    vector<Point> matching_locations;
    // For loops
    // inside for loop: use get_window_mat, similarity_score
    return matching_locations;
}






