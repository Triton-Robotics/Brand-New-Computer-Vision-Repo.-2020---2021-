#ifndef RM_POWERRUNEDETECTOR_H
#define RM_POWERRUNEDETECTOR_H

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video/tracking.hpp"

using namespace cv;
using namespace std;

struct ContourHierarchy
{
    vector<Point> contour;
    int k;
    int hierarchy;
};

class PowerRuneDetector
{
public:
    PowerRuneDetector(string videoPath, string templatePath);

    KalmanFilter kf;
    VideoCapture cap;
    vector<int> bounds;

    // RGB color range for power rune
    Scalar blue_range_lower = Scalar(0, 0, 130);
    Scalar blue_range_higher = Scalar(90, 205, 205);

    void runFullLoop(Range armorArea, Range runeArea, bool draw, int printInterval);
    void setKFValues();
    vector<int> findCropSize(Mat img, string templatePath);
    Point2f detectShootArea(Mat frame, Range armorArea, Range runeArea, bool draw);
};

#endif //RM_POWERRUNEDETECTOR_H
