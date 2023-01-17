//
// Created by Iosif on 17.01.2023.
//

#include "DisplayVideo.h"

#include <utility>
#include <iostream>

DisplayVideo::DisplayVideo(std::string fileSource) {
    this->_fileSource = std::move(fileSource);
    this->_videoCapture = new cv::VideoCapture(this->_fileSource);
}

void DisplayVideo::run() {
    if(!this->_videoCapture->isOpened()) {
        std::cerr << "\nError: The file cannot be opened!";
        return;
    }

    while(true) {
        // Read a frame from video
        cv::Mat frame;
        *this->_videoCapture >> frame;

        // If the frame is empty, stop
        if(frame.empty())
            break;

        cv::imshow("Video", frame);
        cv::waitKey(33);
    }

    this->_videoCapture->release();
    cv::destroyAllWindows();
}

DisplayVideo::~DisplayVideo() {
    delete this->_videoCapture;
}
