//
// Created by Iosif on 23.01.2023.
//

#include "Utilities.h"

cv::Mat Utilities::drawRectangles(const cv::Mat &image, const std::vector<cv::Rect>& rectangles, cv::Point offset) {
    cv::Mat imageDraw;
    image.copyTo(imageDraw);

    for(const auto &r : rectangles) {
        cv::rectangle(imageDraw, cv::Point(r.x + offset.x, r.y + offset.y),
                      cv::Point(r.x + offset.x + r.width, r.y + offset.y + r.height),
                      cv::Scalar(0, 255, 0));
    }

    return imageDraw;
}
