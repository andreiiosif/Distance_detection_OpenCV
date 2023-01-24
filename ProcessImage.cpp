//
// Created by Iosif on 22.01.2023.
//

#include "ProcessImage.h"

ProcessImage::ProcessImage(const cv::Mat &image) {
    this->image=image;
}

std::vector < cv::Rect > ProcessImage::getRectangles() {

    // Turn image to grayscale
    cv::cvtColor(this->image, this->image, cv::COLOR_RGB2GRAY);

    // Display original image
    //cv::imshow("Original image",this->image);

    // Perform blackhat morphological operation to reveal dark regions on white background
    cv::Mat blackhatFrame;
    cv::Mat rectangleKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(13, 5));
    cv::morphologyEx(this->image, blackhatFrame, cv::MORPH_BLACKHAT, rectangleKernel);

    //cv::imshow("Image with blackhat", blackhatFrame);

    // Find license plate based on whiteness property
    cv::Mat lightFrame;
    cv::Mat squareKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(this->image, lightFrame, cv::MORPH_CLOSE, squareKernel);
    cv::threshold(lightFrame, lightFrame, 0, 255, cv::THRESH_OTSU);

    //cv::imshow("Image with light", lightFrame);

    // Compute Sobel gradient from blackhat
    cv::Mat gradX;
    cv::Sobel(blackhatFrame, gradX, CV_32F, 1, 0, 3);
    gradX = cv::abs(gradX);
    cv::convertScaleAbs(gradX, gradX);

    //cv::imshow("Image blackhat + Sobel", gradX);

    // Blur the Gradient and apply a close operation
    cv::GaussianBlur(gradX, gradX, cv::Size(5, 5), 0);
    cv::morphologyEx(gradX, gradX, cv::MORPH_CLOSE, rectangleKernel);
    cv::threshold(gradX, gradX, 0, 255, cv::THRESH_OTSU);

    //cv::imshow("Image bS gradient and close", gradX);

    // Erode and dilate
    cv::erode(gradX, gradX, 2);
    cv::dilate(gradX, gradX, 2);

    //cv::imshow("Image gradient with erode and dilate", gradX);

    // Bitwise and between gradX and lightFrame
    cv::bitwise_and(gradX, lightFrame, gradX);
    cv::dilate(gradX, gradX, 2);
    cv::erode(gradX, gradX, 1);

    //cv::imshow("Bitwise image gradX and lightFrame", gradX);

    // Get contours
    std::vector < std::vector < cv::Point > > contours;
    cv::findContours(gradX, contours, cv::noArray(), cv::RETR_EXTERNAL,
                     cv::CHAIN_APPROX_SIMPLE);

    // Filter out nonrectangle shapes
    contours.erase(std::remove_if(contours.begin(), contours.end(),
                                  [](auto &a) { return cv::boundingRect(a).area() - cv::contourArea(a) > RECT_FILTER; }), contours.end());

    std::vector < cv::Rect > rectangles;
    std::transform(contours.begin(), contours.end(), std::back_inserter(rectangles),
                   [](const auto &a) { return cv::boundingRect(a); });

    // Filter rectangles with width > height
    std::vector < cv::Rect > filteredRectangles;
    std::copy_if(rectangles.begin(), rectangles.end(), std::back_inserter(filteredRectangles),
                 [](const auto &a) { return a.height < a.width; });

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
