//
// Created by Iosif on 23.01.2023.
//

#ifndef IMAGE_PROCESSING_TEMPLATE_UTILITIES_H
#define IMAGE_PROCESSING_TEMPLATE_UTILITIES_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/utility.hpp>

class Utilities {
public:
    static cv::Mat drawRectangles(const cv::Mat &image, const std::vector < cv::Rect >& rectangles, cv::Point offset);
    static std::vector < std::vector < cv::Point > > getContoursFromImage(const cv::Mat &image);
    static double getRealDistance(const cv::Rect licensePlate, double FOV, int32_t imageWidth);
};


#endif //IMAGE_PROCESSING_TEMPLATE_UTILITIES_H
