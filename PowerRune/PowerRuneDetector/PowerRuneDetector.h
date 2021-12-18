//
// Created by Shangzheng Ji on 11/13/21.
//

#ifndef RM_POWERRUNEDETECTOR_H
#define RM_POWERRUNEDETECTOR_H
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include <iostream>
using namespace std;
using namespace cv;

struct ContourHierarchy {
    vector<Point> contour;
    int k;
    int hierarchy;
};

class PowerRuneDetector {

public:
    cv::Mat result;
    cv::Mat RGBim;
    PowerRuneDetector();
    ~PowerRuneDetector() = default;
    // starter function of bigbuff (an analog of the entry of assembly line)
    void feed_im(cv::Mat &input_image);

    // to predict bigbuff's next spatial information (under construction)
    void make_prediction();

private:
    void filteImage(cv::Mat &im, uint8_t color);

    // find the object in a BINARY IMAGE by recognizing its GEOMETRY
    bool locate_target(cv::Mat &im);

    // a HELPER FUNCTION to check whether the CONTOUR is wanted
    bool contour_valid(std::vector<cv::Point> &contour);

    // a HELPER FUNCTION to draw a smallest circumscribed rectangle
    void drawContour_Rec(cv::RotatedRect rect, cv::Mat &src);
};


#endif //RM_POWERRUNEDETECTOR_H
