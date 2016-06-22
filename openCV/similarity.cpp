#include "similarity.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
using namespace cv;

// Given two matrices, get the unnormed cosine similarity of the two matrices
double correlation(Mat template_mat, Mat img_window_mat) {
    double result = template_mat.dot(img_window_mat);
    return result;
}

// Given two matrices, get the cosine similarity of the two matrices
double correlation_normed(Mat template_mat, Mat img_window_mat) {
    double correlation_res = correlation(template_mat, img_window_mat);
    double result = correlation_res / (norm(template_mat) * norm(img_window_mat));
    return result;
}

// Given two matrices, get the square difference of the two matrices
double square_diff(Mat template_mat, Mat img_window_mat) {
    double result_sqrt = norm(template_mat, img_window_mat);
    return result_sqrt * result_sqrt;
}

// Given two matrices, get the normed square difference of the two matrices
double square_diff_normed(Mat template_mat, Mat img_window_mat) {
    double square_diff_res = square_diff(template_mat, img_window_mat);
    double result = square_diff_res / (norm(template_mat) * norm(img_window_mat));
    return result;
}

// Get the matrix of same size where every value is the mean value of the original matrix
Mat get_mean_mat(Mat input_mat) {
    double mean_val = sum(input_mat)[0] / (input_mat.rows * input_mat.cols);
    Mat mean_mat = Mat::ones(input_mat.rows, input_mat.cols, CV_32FC1) * mean_val;
    return mean_mat;
}

// Subtract the mean value matrix from the original matrix
Mat get_deviation_mat(Mat input_mat) {
    return (input_mat - get_mean_mat(input_mat));
}

// Input: template matrix and window matrix in the image.
// For the two given matrices, subtract an average pixel value
// from each pixel and get two deviation matrices Then do the dot product of the
// two deviation matrices,
// output is the dot product of the deviation matrices
double coefficient(Mat template_mat, Mat img_window_mat) {
    return correlation(get_deviation_mat(template_mat), get_deviation_mat(img_window_mat));
}


// Input: template matrix and window matrix in the image.
// For the two given matrices, subtract an average pixel value
// from each pixel and get two deviation matrices Then do the dot product of the
// two deviation matrices,
// output is the cosine similarity of the deviation matrices
double coefficient_normed(Mat template_mat, Mat img_window_mat) {
    double coefficient_res = coefficient(template_mat, img_window_mat);
    double result = coefficient_res / (norm(get_deviation_mat(template_mat)) * norm(get_deviation_mat(img_window_mat)));
    return result;
}

Method_map_t method_map = std::map<std::string, double(*)(Mat, Mat)> {
    {"correlation", &correlation},
    {"correlation_normed", &correlation_normed},
    {"square_diff", &square_diff},
    {"square_diff_normed", &square_diff_normed},
    {"coefficient", &coefficient},
    {"coefficient_normed", &coefficient_normed}
};

double get_similarity_score(std::string method, Mat template_mat, Mat img_window_mat) {
    return method_map[method](template_mat, img_window_mat);
}

