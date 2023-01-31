//
// Created by Iosif on 22.01.2023.
//

#include "ProcessImage.h"
#include "../Utilities/Utilities.h"

ProcessImage::ProcessImage(const cv::Mat &image) {
    this->_image=image;
}

std::vector < cv::Rect > ProcessImage::getRectangles() {
    // Turn _image to grayscale
    cv::cvtColor(this->_image, this->_image, cv::COLOR_RGB2GRAY);

    // Get contours
    std::vector < std::vector < cv::Point > > contours = Utilities::getContoursFromImage(this->_image);

    // Filter out nonrectangle shapes
    contours.erase(std::remove_if(contours.begin(), contours.end(),
                                  [](auto &a) { return cv::boundingRect(a).area() - cv::contourArea(a) > RECT_FILTER; }), contours.end());

    std::vector < cv::Rect > rectangles;
    std::transform(contours.begin(), contours.end(), std::back_inserter(rectangles),
                   [](const auto &a) { return cv::boundingRect(a); });

    // Filter rectangles with width to weight ratio between 3 and 6
    std::vector < cv::Rect > filteredRectangles;
    std::copy_if(rectangles.begin(), rectangles.end(), std::back_inserter(filteredRectangles),
                 [](const auto &a) {
        return (float)a.width / a.height >= MIN_AR && (float)a.width / a.height <= MAX_AR && a.area() > RECT_AREA;
    });

    // Keep the biggest 5 rectangles
    std::sort(filteredRectangles.begin(), filteredRectangles.end(), [](const auto &a, const auto &b) {
       return a.area() < b.area();
    });

    if(filteredRectangles.size() > 5) {
        std::vector < cv::Rect >  bestFiltered(filteredRectangles.end() - 5, filteredRectangles.end());
        return bestFiltered;
    }

    return filteredRectangles;
}
