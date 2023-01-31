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

std::vector<std::vector<cv::Point> > Utilities::getContoursFromImage(const cv::Mat &image) {
    // Perform blackhat morphological operation to reveal dark regions on white background
    cv::Mat blackhatFrame;
    cv::Mat rectangleKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(13, 5));
    cv::morphologyEx(image, blackhatFrame, cv::MORPH_BLACKHAT, rectangleKernel);

    //cv::imshow("Image with blackhat", blackhatFrame);

    // Find license plate based on whiteness property
    cv::Mat lightFrame;
    cv::Mat squareKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(image, lightFrame, cv::MORPH_CLOSE, squareKernel);
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

    //cv::imshow("Bitwise _image gradX and lightFrame", gradX);
    std::vector < std::vector < cv::Point > > contours;
    cv::findContours(gradX, contours, cv::noArray(), cv::RETR_EXTERNAL,
                     cv::CHAIN_APPROX_SIMPLE);

    return contours;
}

double Utilities::getRealDistance(const cv::Rect licensePlate, double FOV, int32_t imageWidth) {
    // Get L1 and L2
    double licenseLength = licensePlate.width;
    double imageLength = imageWidth;

    // Get L3
    double realLicenseLength = 52.0;

    // Get direct Distance
    double distance = imageLength * realLicenseLength * 0.5 / (licenseLength * tan(FOV));

    return distance;
}


