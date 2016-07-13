#include "get_multi_location_and_rotation.h"


using namespace std;
using namespace cv;


vector<center_and_angle_t> get_multi_location_and_rotation(const Mat & templ_img, const Mat & test_img, double rotation_start, double rotation_end, double rotation_stride){
	Mat tmp_score;
	Mat max_score = Mat::zeros(test_img.rows - templ_img.rows + 1, test_img.cols - templ_img.cols + 1, CV_32F);
	Mat best_pos = Mat::zeros(test_img.rows - templ_img.rows + 1, test_img.cols - templ_img.cols + 1, CV_32F);
	cout << max_score.at<float>(0, 0) << endl;

	int nearby_size = 5;
	double threshold = 100;
	
	for (int angle = rotation_start; angle < rotation_end; angle += rotation_stride){
		Mat rotated_tmp_score = cal_similarity_score(templ_img, test_img, angle);
		cout << rotated_tmp_score.at<float>(0, 0) << endl;
		// rotate the Mat back to original direction
		int side_length = sqrt(rotated_tmp_score.cols * rotated_tmp_score.cols + rotated_tmp_score.rows * rotated_tmp_score.rows);
		//cout << side_length << endl;
		Rect myROI(side_length / 2 - test_img.cols / 2 + templ_img.cols / 2, side_length / 2 - test_img.rows / 2 + templ_img.rows / 2, test_img.cols - templ_img.cols + 1, test_img.rows - templ_img.rows + 1);
		//cout << myROI.height << endl;
		//cout << myROI.width << endl;
		//cout << myROI.x << endl;
		//cout << myROI.y << endl;
		tmp_score = rotate_and_crop(rotated_tmp_score, - angle, myROI, false);
		//imshow("test", tmp_score);
		//waitKey(0);
		cout << tmp_score.at<float> (100, 100);
		pair_wise_mat_max(max_score, tmp_score, best_pos, angle);
		//break;

	}
	return find_object(max_score, best_pos, nearby_size, threshold);
}

// best_pos is passed by reference
// max_score is passed by reference
void pair_wise_mat_max(Mat & max_score, const Mat & tmp_score, Mat & best_pos, int angle){
	// remember to check if the size are the same
	if (max_score.cols != tmp_score.cols || max_score.rows != tmp_score.rows){
		cout << max_score.cols << tmp_score.cols << endl;
		cout << max_score.rows << tmp_score.rows << endl;
		cout << "Alert! Different Mat size" << endl;
		return;
	}
	for (int i = 0; i < max_score.rows; i ++){
		for (int j = 0; j < max_score.cols; j ++){
			if (max_score.at<float>(i, j) < tmp_score.at<float>(i, j)){
				max_score.at<float>(i, j) = tmp_score.at<float>(i, j);
				//cout << max_score.at<float>(i, j) << endl;
				best_pos.at<float>(i, j) = angle;
			}
		}
	}

	return;
}








