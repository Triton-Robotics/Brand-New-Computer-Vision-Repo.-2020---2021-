#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include <iostream>
#include <chrono>
#include <math.h>
#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;

// TO DO
// Pull magic constants out and possibly parametrize them
// More configuration options (like no template, verbose, etc)
// Maybe restructure so loop is called outside class

struct ContourHierarchy
{
    vector<Point> contour;
    int k;
    int hierarchy;
};

class PowerRuneDetector
{
public:
    KalmanFilter kf;
    VideoCapture cap;
    vector<int> bounds;

    // RGB color range for power rune
    // Should probably convert to HSV for easier tuning
    Scalar blue_range_lower = Scalar(0, 0, 130);
    Scalar blue_range_higher = Scalar(90, 205, 205);

    vector<int> findCropSize(Mat img, string templatePath);
    Mat detectShootArea(Mat frame, Range armorArea, Range runeArea);
    cv::Point2f findPitchYaw(cv::Point2f points);

    PowerRuneDetector(string videoPath, string templatePath)
    {
        cap = VideoCapture(videoPath);

        if (!cap.isOpened())
        {
            cout << "Error opening video stream or file" << endl;
            return;
        }

        Mat frame;
        cap >> frame;
        bounds = findCropSize(frame, templatePath);

        setKFValues();
    };

    void runMainLoop(Range armorArea, Range runeArea)
    {
        auto start = chrono::system_clock::now();
        int numFrames = 0;
        Mat frame;
        while (1)
        {
            cap >> frame;

            if (frame.empty())
                break;

            Mat newFrame = detectShootArea(frame, armorArea, runeArea);
            imshow("frame", newFrame);

            numFrames++;

            // Exit video capture if "q" is pressed
            char c = (char)waitKey(1);
            if (c == 113)
                break;
        }

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        cout << "Average FPS: " << numFrames / elapsed_seconds.count() << endl;

        cap.release();
        destroyAllWindows();
    }

    void setKFValues()
    {
        kf = KalmanFilter(4, 2);
        kf.measurementMatrix = Mat::eye(2, 4, CV_32F);
        kf.transitionMatrix = Mat::eye(4, 4, CV_32F);
        kf.transitionMatrix.at<float>(2) = 1.0f;
        kf.transitionMatrix.at<float>(7) = 1.0f;
        kf.processNoiseCov = Mat::eye(4, 4, CV_32F) * 1e-8;
        kf.measurementNoiseCov = Mat::eye(2, 2, CV_32F) * 1e-6;
        kf.errorCovPost = Mat::eye(4, 4, CV_32F);
    };
};

// Identifies panel to shoot and runs Kalman Filter to predict position
// armorArea is the actual square on the power rune arm
// runeArea is the full power rune arm (sort of hammer shaped)
Mat PowerRuneDetector::detectShootArea(Mat frame, Range armorArea, Range runeArea)
{
    frame = frame(Range(bounds[0], bounds[1]),
                  Range(bounds[2], bounds[3]));

    // General image cleaning by blurring and closing holes to reduce noise
    Mat blurred, mask_img, mask, morph_img;
    GaussianBlur(frame, blurred, Size(7, 7), 0);
    cvtColor(blurred, mask_img, COLOR_BGR2RGB);
    inRange(mask_img, blue_range_lower, blue_range_higher, mask);
    morphologyEx(mask, morph_img, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(7, 7)));

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(morph_img, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);

    if (contours.size() > 0)
    {
        vector<ContourHierarchy> contourHierarchy;
        // Custom struct to be able to sort while keeping track of hierarchy
        // Need to track this to associate correct rune to correct armor
        for (int k = 0; k < contours.size(); k++)
        {
            ContourHierarchy curr{contours[k], k, hierarchy[k][3]};
            contourHierarchy.push_back(curr);
        }

        // Sort with smallest area first so armor modules are processed before full rune
        sort(contourHierarchy.begin(), contourHierarchy.end(), [](const ContourHierarchy &c1, const ContourHierarchy &c2)
             { return contourArea(c1.contour) < contourArea(c2.contour); });

        vector<int> armorModule;
        for (int i = 0; i < contourHierarchy.size(); i++)
        {
            double area = contourArea(contourHierarchy[i].contour);
            if ((area >= armorArea.start) && (area <= armorArea.end))
            {
                armorModule.push_back(i);
            }
            else if ((area >= runeArea.start) && (area <= runeArea.end))
            {
                for (int j = 0; j < armorModule.size(); j++)
                {
                    // Check which armor module given rune corresponds to
                    if (contourHierarchy[armorModule[j]].hierarchy == contourHierarchy[i].k)
                    {
                        Point2f center;
                        float radius;
                        minEnclosingCircle(contourHierarchy[armorModule[j]].contour, center, radius);
                        // Print future position using KF and current position
                        Mat measurement = (Mat_<float>(2, 1) << (int)center.x, (int)center.y);
                        Mat prediction = kf.predict();
                        kf.correct(measurement);

                        // Draw current position and where to shoot on frame
                        // Will need to be changed to return actual position when
                        // eventually interfacing with embedded shooter
                        Point2f newCenter{(int)prediction.at<float>(0, 0) + 15 * prediction.at<float>(0, 2), (int)prediction.at<float>(0, 1) + 15 * prediction.at<float>(0, 3)};

                        circle(frame, newCenter, radius, Scalar(255, 0, 0), 2);
                        circle(frame, center, radius, Scalar(0, 0, 255), 2);
                    }
                }
            }
        }
    }

    return frame;
}

// Use template matching to greatly decrease area needed to search and increase speed
vector<int> PowerRuneDetector::findCropSize(Mat img, string templatePath)
{
    Mat imgGray, imgGaus;
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    Mat templateGray = imread(templatePath, IMREAD_GRAYSCALE);
    Size s = templateGray.size();
    int w = s.width;
    int h = s.height;
    adaptiveThreshold(imgGray, imgGaus, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, -10);

    // How large of an area around the template to save
    int radiusRatio = 8;
    // Some scales between 0.4x size and 1x size
    vector<float> linspace;
    float start = 0.4;
    float end = 1;
    int numIn = 5;

    for (int i = 0; i < numIn; i++)
    {
        linspace.push_back(start + i * (end - start) / (numIn - 1));
    }

    // Test if template at various sizes exists in the frame, returns the closest matching center
    vector<float> found{0, 0, 0, 0};
    for (float scale : linspace)
    {
        float rW = w * scale;
        float rH = h * scale;
        Mat resized, res;
        resize(templateGray, resized, Size(rW, rH), INTER_AREA);
        matchTemplate(imgGaus, resized, res, TM_CCOEFF_NORMED);

        double minVal, maxVal;
        Point minLoc, maxLoc;
        minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);

        if (maxVal > found[0])
        {
            found[0] = maxVal;
            found[1] = maxLoc.x;
            found[2] = maxLoc.y;
            found[3] = scale;
        }
    }

    vector<int> shape{(int)(found[3] * w), (int)(found[3] * h)};
    int center_x = found[1] + (0.5 * shape[0]);
    int center_y = found[2] + (0.5 * shape[1]);
    int radius = radiusRatio * shape[0];

    // Bounds of the cropped area
    vector<int> ret{center_y - radius, center_y + radius,
                    center_x - radius, center_x + radius};

    return ret;
}

cv::Point2f rotatePoint(const cv::Point2f& centerPoint, const cv::Point2f& inPoint, const double& angRad) {
    cv::Point2f rotatedPoint;
    rotatedPoint.x = ((inPoint.x - centerPoint.x) * cos(angRad)) - ((inPoint.y - centerPoint.y) * sin(angRad)) + centerPoint.x;
    rotatedPoint.y = ((inPoint.x - centerPoint.x) * sin(angRad)) + ((inPoint.y - centerPoint.y) * cos(angRad)) + centerPoint.y;
    return rotatedPoint;
}

//TODO
cv::Point2f PowerRuneDetector::findPitchYaw(cv::Point2f points) {
    //cv::solvePnP(3Dpoints, 2Dpoints, cameraMatrix, distCoeffs, rvec, tvec);

    //Finds the center of the power rune from the bounds
    int center_y = floor((bounds[1] - bounds[0])/2) + bounds[0];
    int center_x = floor((bounds[3] - bounds[2])/2) + bounds[2];
    cv::Point2f runeCenterPoint(center_x, center_y);
    //The x and y value of the target point
    int x_aim = points.x;
    int y_aim = points.y;
    //Finding the x and y difference between the center and the predicted point
    int x = x_aim - center_x;
    int y = y_aim - center_y;
    cv::Point2f centerTargetPoint(x_aim, y_aim);
    //Using the pixel distance and actual distance to create a conversion
    //from mm to pixel distances
    int RADIUS_TO_CENTER_OF_PLATE = 700;
    double mmToPix = (hypot(x,y))/RADIUS_TO_CENTER_OF_PLATE;

    //Coordinates of the prediction rectangle if it was directly to the right of
    //the center of the Power Rune
    int Y_OFFSET_FROM_CENTER = floor(130 * mmToPix);
    int X_TOP_CORNER_OFFSET_FROM_CENTER = floor(800 * mmToPix);
    int X_BOTTOM_CORNER_OFFSET_FROM_CENTER = floor(700 * mmToPix);
    cv::Point2f topLeftCorner(center_x + X_TOP_CORNER_OFFSET_FROM_CENTER, center_y - Y_OFFSET_FROM_CENTER);
    cv::Point2f topRightCorner(center_x + X_TOP_CORNER_OFFSET_FROM_CENTER, center_y + Y_OFFSET_FROM_CENTER);
    cv::Point2f bottomLeftCorner(center_x + X_BOTTOM_CORNER_OFFSET_FROM_CENTER, center_y - Y_OFFSET_FROM_CENTER);
    cv::Point2f bottomRightCorner(center_x + X_BOTTOM_CORNER_OFFSET_FROM_CENTER, center_y + Y_OFFSET_FROM_CENTER);

    //Calculating rotation of points
    double angleOfRotation = atan2(y_aim - center_y, x_aim - center_x);
    cv::Point2f rotatedTopLeftCorner = rotatePoint(runeCenterPoint, topLeftCorner, angleOfRotation);
    cv::Point2f rotatedTopRightCorner = rotatePoint(runeCenterPoint, topRightCorner, angleOfRotation);
    cv::Point2f rotatedBottomLeftCorner = rotatePoint(runeCenterPoint, bottomLeftCorner, angleOfRotation);
    cv::Point2f rotatedBottomRightCorner = rotatePoint(runeCenterPoint, bottomRightCorner, angleOfRotation);

    vector<Point2f> imgPoints = vector<Point2f>{
        rotatedTopLeftCorner,
        rotatedTopRightCorner,
        rotatedBottomRightCorner,
        rotatedBottomLeftCorner
    };

    int HALF_Y_LENGTH = 100;
    int HALF_X_LENGTH = 130;
    vector<Point3f> objPoints = vector<Point3f>{
            cv::Point3f(- HALF_X_LENGTH , - HALF_Y_LENGTH , 0),	//tl
            cv::Point3f( HALF_X_LENGTH , - HALF_Y_LENGTH , 0),	//tr
            cv::Point3f( HALF_X_LENGTH,HALF_Y_LENGTH , 0),	//br
            cv::Point3f(- HALF_X_LENGTH , HALF_Y_LENGTH , 0)	//bl
    };

    cv:: Mat rVec = cv:: Mat ::zeros(3, 1, CV_64FC1 );//init rvec
    cv:: Mat tVec = cv:: Mat ::zeros(3, 1, CV_64FC1 );//init tvec

    solvePnP( objPoints , imgPoints , cam , NULL , rVec , tVec , false , cv::SOLVEPNP_ITERATIVE );

    float yaw = tan(tVec.at<float>(0)/tVec.at<float>(2));
    float pitch = tan(tVec.at<float>(1)/tVec.at<float>(2));

    cv::Point2f pitchYaw(pitch, yaw);
}

int main()
{
    PowerRuneDetector prd("/home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/assets/power_rune.mp4", "/home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/assets/template.jpg");
    // Constants given work for video, would need to be tuned
    prd.runMainLoop(Range(1430, 1600), Range(3000, 4500));
    return 1;
}