#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;

// TO-DO
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
    findContours(morph_img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

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

int main()
{
    PowerRuneDetector prd("assets/power_rune.mp4", "assets/template.jpg");
    // Constants given work for video, would need to be tuned
    prd.runMainLoop(Range(1430, 1600), Range(3000, 4500));
    return 1;
}