//
// Created by Shangzheng Ji on 11/13/21.
//

#include "PowerRuneDetector.h"

PowerRuneDetector::PowerRuneDetector() {
    KalmanFilter kf(4, 2);
    kf.measurementMatrix = Mat::eye(2, 4, CV_32F);
    kf.transitionMatrix = Mat::eye(4, 4, CV_32F);
    kf.transitionMatrix.at<float>(2) = 1.0f;
    kf.transitionMatrix.at<float>(7) = 1.0f;
    kf.processNoiseCov = Mat::eye(4, 4, CV_32F) * 1e-8;
    kf.measurementNoiseCov = Mat::eye(2, 2, CV_32F) * 1e-6;
    kf.errorCovPost = Mat::eye(4, 4, CV_32F);
}

void PowerRuneDetector::filteImage(Mat &im, uint8_t color) {

}

bool PowerRuneDetector::locate_target(Mat &im) {
    return false;
}

bool PowerRuneDetector::contour_valid(vector<cv::Point> &contour) {
    return false;
}

void PowerRuneDetector::drawContour_Rec(cv::RotatedRect rect, Mat &src) {

}

void PowerRuneDetector::feed_im(Mat &input_image) {

}

void PowerRuneDetector::make_prediction() {

}

