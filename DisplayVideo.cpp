//
// Created by Iosif on 17.01.2023.
//

#include "DisplayVideo.h"
#include "ProcessImage.h"
#include "Utilities.h"

#include <utility>
#include <iostream>
#include <chrono>

DisplayVideo::DisplayVideo(std::string fileSource) {
    // Initialize fields for DisplayVideo class
    this->_fileSource = std::move(fileSource);
    this->_videoCapture = new cv::VideoCapture(this->_fileSource);
}

void DisplayVideo::run() {
    // Test if file can be open or if it exists
    if(!this->_videoCapture->isOpened()) {
        std::cerr << "\nError: The file cannot be opened!";
        return;
    }

    // Display video, frame by frame, in a loop
    while(true) {
        // Read a frame from video
        cv::Mat frame;
        *this->_videoCapture >> frame;

        // If the frame is empty, stop
        if(frame.empty())
            break;

        // Execution time of each frame

        // Get starting timepoint
        auto start = std::chrono::high_resolution_clock::now();

        auto ROI = cv::Rect(220, 239, 400, 240);
        auto imageToProcess = frame(ROI);

        auto processImage = ProcessImage(imageToProcess);
        auto rectangles = processImage.getRectangles();
        auto processedImage = Utilities::drawRectangles(frame, rectangles, cv::Point(220, 239));

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout << "Execution time of frame: " << duration.count() << "ms.\n";

        cv::imshow("Video", processedImage);
        cv::waitKey(33);
    }

    this->_videoCapture->release();
    cv::destroyAllWindows();
}

DisplayVideo::~DisplayVideo() {
    delete this->_videoCapture;
}
