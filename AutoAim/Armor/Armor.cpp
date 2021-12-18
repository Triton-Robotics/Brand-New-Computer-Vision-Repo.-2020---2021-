//
// Created by Shangzheng Ji on 11/13/21.
//

#include "Armor.h"
using namespace cv;
Armor::Armor(const LED_bar &left, const LED_bar &right) {
    this->left = left;
    this->right = right;
    error_angle = fabs(left.rotatedRect.angle - right.rotatedRect.angle);
    rect.width = abs(static_cast<int>(left.rotatedRect.center.x - right.rotatedRect.center.x));
    rect.height = static_cast<int>((left.rotatedRect.size.height + right.rotatedRect.size.height) / 2);
    center.x = static_cast<int>((left.rotatedRect.center.x + right.rotatedRect.center.x) / 2);
    center.y = static_cast<int>((left.rotatedRect.center.y + right.rotatedRect.center.y) / 2);
    rect.x = center.x - rect.width / 3;
    rect.y = center.y - rect.height / 3;
    rect.width *= 2 / 3;
    rect.height *= 2 / 3;
}
/**
 *
 * @param img the input image
 * @return the intensity of the
 */
int Armor::get_average_intensity(const cv::Mat &img) {
    if (rect.width < 1 || rect.height < 1 || rect.x < 1 || rect.y < 1
        || rect.width + rect.x > img.cols || rect.height + rect.y > img.rows)
        return 255;
    Mat roi = img(Range(rect.y, rect.y + rect.height), Range(rect.x, rect.x + rect.width));
    this->average_intensity = static_cast<int>(mean(roi).val[0]);
    return this->average_intensity;
}

void Armor::draw_Armor(Mat &image, cv::Point2f roi_offset, bool drawCenter) const {
    rectangle(image, rect + Point_<int>(roi_offset), Scalar(255, 255, 255), 1);
    if(drawCenter) {
        circle(image, center + Point_<int>(roi_offset), int(rect.height / 4), Scalar(0, 0, 255), -1);
    }
}

bool Armor::Armor_constraints() {
    //TODO: read the Armor constraints from config file to tune the threshold.
    double distance = Euclidean_distance();
    double center_height_difference = this->center_height_difference();
    double height_ratio = this->height_ratio();
    double armor_width = width_two_center();
    double average_height = (left.rotatedRect.size.height + right.rotatedRect.size.height) / 2.f;
    double height_width_ratio = this->height_width_ratio();
    if (distance < 575.0f &&
        height_ratio < 1.5f &&
        left.rotatedRect.size.width < armor_width &&
        right.rotatedRect.size.width < armor_width &&
        3 * (left.rotatedRect.size.width + right.rotatedRect.size.width) < armor_width && // to prevent two led bars closing to each other.
        center_height_difference < average_height &&//  to prevent excessive center difference in y-axis.
        height_width_ratio < 4.0 && height_ratio > 1) {
        return true;
    }
    return false;
}

void Armor::match_LEDs(std::vector<LED_bar> &LEDs, size_t i, size_t j) {
    if ()
}
