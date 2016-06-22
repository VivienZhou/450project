#ifndef SMILARITY_H
#define SMILARITY_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <map>
using cv::Mat;

// Given two matrices, get the unnormed cosine similarity of the two matrices
double correlation(Mat template_mat, Mat img_window_mat);

// Given two matrices, get the cosine similarity of the two matrices
double correlation_normed(Mat template_mat, Mat img_window_mat);

// Given two matrices, get the square difference of the two matrices
double square_diff(Mat template_mat, Mat img_window_mat);

// Given two matrices, get the normed square difference of the two matrices
double square_diff_normed(Mat template_mat, Mat img_window_mat);

// Get the matrix of same size where every value is the mean value of the original matrix
Mat get_mean_mat(Mat input_mat);

// Subtract the mean value matrix from the original matrix
Mat get_deviation_mat(Mat input_mat);

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

using Method_map_t = std::map<std::string, double(*)(Mat, Mat)>;

// This is the main function used by client
// method is one of the followings: "correlation", "correlation_normed", "square_diff", "square_diff_normed", "coefficient", "coefficient_normed"
// template_mat is the matrix of the template image
// img_window_mat is the matrix captured from the original image matrix
double get_similarity_score(std::string method, Mat template_mat, Mat img_window_mat);


#endif
