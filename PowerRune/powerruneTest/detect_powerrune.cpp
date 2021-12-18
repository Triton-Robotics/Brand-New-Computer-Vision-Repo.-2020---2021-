#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Scalar blue_range_lower = Scalar(0, 0, 130);
Scalar blue_range_higher = Scalar(90, 205, 205);

vector<int> findCropSize(Mat img);

struct ContourHierarchy {
  vector<Point> contour;
  int k;
  int hierarchy;
};

int main(){
	KalmanFilter kf(4, 2);
	kf.measurementMatrix = Mat::eye(2, 4, CV_32F);
	kf.transitionMatrix = Mat::eye(4, 4, CV_32F);
	kf.transitionMatrix.at<float>(2) = 1.0f;
	kf.transitionMatrix.at<float>(7) = 1.0f;
	kf.processNoiseCov = Mat::eye(4, 4, CV_32F) * 1e-8;
    kf.measurementNoiseCov = Mat::eye(2, 2, CV_32F) * 1e-6;
    kf.errorCovPost = Mat::eye(4, 4, CV_32F);

	VideoCapture cap("assets/power_rune.mp4"); 
   
	if(!cap.isOpened()){
		cout << "Error opening video stream or file" << endl;
    	return -1;
	}

	Mat frame;
    cap >> frame;
	vector<int> bounds = findCropSize(frame);
	
  	while(1) {
		Mat frame;
		cap >> frame;
	 
		if (frame.empty())
		  break;

		frame = frame(Range(bounds[0], bounds[1]), 
					  Range(bounds[2], bounds[3]));
		Mat contour_frame = frame.clone();

		Mat blurred, mask_img, mask, morph_img;
		GaussianBlur(frame, blurred, Size(7, 7), 0);
		cvtColor(blurred, mask_img, COLOR_RGB2BGR);
		inRange(mask_img, blue_range_lower, blue_range_higher, mask);
		morphologyEx(mask, morph_img, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(7,7)));

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(morph_img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

    	if (contours.size() > 0) {
			vector<ContourHierarchy> contourHierarchy;
			for (int k = 0; k < contours.size(); k++) {
				ContourHierarchy curr{contours[k], k, hierarchy[k][3]};
				contourHierarchy.push_back(curr);
			}
			sort(contourHierarchy.begin(), contourHierarchy.end(), [](const ContourHierarchy& c1, const ContourHierarchy& c2) {
    			return contourArea(c1.contour) < contourArea(c2.contour);
			});

			vector<int> armorModule;
			for (int i = 0; i < contourHierarchy.size(); i++) {
				double area = contourArea(contourHierarchy[i].contour);
				if ((area >= 1430) && (area <= 1600)) {
					armorModule.push_back(i);
				} else if ((area >= 3000) && (area <= 4500)) {
					for (int j = 0; j < armorModule.size(); j++) {
						if (contourHierarchy[armorModule[j]].hierarchy == contourHierarchy[i].k) {
							Point2f center;
							float radius;
							minEnclosingCircle(contourHierarchy[armorModule[j]].contour, center, radius);
							Mat measurement = (Mat_<float>(2, 1) << (int) center.x, (int) center.y);
							Mat prediction = kf.predict();
							kf.correct(measurement);

							Point2f newCenter{(int) prediction.at<float>(0,0) + 15 * prediction.at<float>(0,2), (int) prediction.at<float>(0,1) + 15 * prediction.at<float>(0,3)};
							circle(frame, newCenter, radius, Scalar(255, 0, 0), 2);
							circle(frame, center, radius, Scalar(0, 0, 255), 2);
						}
					}

							
	
				}
			}
		}

		// Press  q on keyboard to exit
		imshow("test", frame);
		char c=(char)waitKey(1);
		if(c==113)
		  break;
  	}
 
	  cap.release();
	  destroyAllWindows();
	
  	return 0;
}

vector<int> findCropSize(Mat img) {
	Mat imgGray, imgGaus;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	Mat templateGray = imread("assets/template.jpg", IMREAD_GRAYSCALE);
	Size s = templateGray.size();
	int w = s.width;
	int h = s.height;
	adaptiveThreshold(imgGray, imgGaus, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, -10);
	int radiusRatio = 8;
	vector<float> linspace;
	float start = 0.4;
	float end = 1;
	int numIn = 5;

	for (int i = 0; i < numIn; i++) {
		linspace.push_back(start + i * (end - start) / (numIn - 1));
	}

	vector<float> found{0, 0, 0, 0};
	
	for (float scale : linspace) {
		float rW = w * scale;
		float rH = h * scale;
		Mat resized, res;
		resize(templateGray, resized, Size(rW, rH), INTER_AREA);
		matchTemplate(imgGaus, resized, res, TM_CCOEFF_NORMED);

		double minVal, maxVal;
		Point minLoc, maxLoc;
		minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);

		if (maxVal > found[0]) {
			found[0] = maxVal;
			found[1] = maxLoc.x;
			found[2] = maxLoc.y;
			found[3] = scale;
		}
	}

	vector<int> shape{(int) (found[3] * w), (int) (found[3] * h)};
	int center_x = found[1] + (0.5 * shape[0]);
	int center_y = found[2] + (0.5 * shape[1]);
	int radius = radiusRatio * shape[0];

	vector<int> ret{center_y - radius, center_y + radius, 
					  center_x - radius, center_x + radius};

	return ret;
}
