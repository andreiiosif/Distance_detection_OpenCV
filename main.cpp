#pragma ide diagnostic ignored "EndlessLoop"

#include <iostream>
#include "DisplayVideo/DisplayVideo.h"
#include "Image/ProcessImage.h"
#include "Utilities/Utilities.h"

int main()
{
    // Read video from file
    //auto videoCapture = DisplayVideo("Video/filmare_bord_cut.mp4");
    //videoCapture.run();

    // Calculate real distance using an image
    cv::Mat image = cv::imread("Video/test_image.png", cv::IMREAD_COLOR);

    auto ROI = cv::Rect(340, 359, 600, 360);
    auto imageToProcess = image(ROI);

    auto processImage = ProcessImage(imageToProcess);
    auto rectangles = processImage.getRectangles();
    auto processedImage = Utilities::drawRectangles(image, rectangles, cv::Point(340, 359));

    double distance = Utilities::getRealDistance(rectangles[0], CV_PI / 3, image.cols);

    cv::imshow("Image", processedImage);
    std::cout << "Real distance is: " << distance << "cm.";

    cv::waitKey(0);

    return 0;
}