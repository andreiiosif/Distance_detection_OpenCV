//
// Created by Iosif on 22.01.2023.
//

#ifndef IMAGE_PROCESSING_TEMPLATE_PROCESSIMAGE_H
#define IMAGE_PROCESSING_TEMPLATE_PROCESSIMAGE_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/utility.hpp>

#define RECT_FILTER 2000
#define MIN_AR 3
#define MAX_AR 6
#define RECT_AREA 100

class ProcessImage {
private:
    cv::Mat _image;
public:
    explicit ProcessImage(const cv::Mat &image);
    std::vector < cv::Rect > getRectangles();
};


#endif //IMAGE_PROCESSING_TEMPLATE_PROCESSIMAGE_H
