//
// Created by Iosif on 17.01.2023.
//

#ifndef IMAGE_PROCESSING_TEMPLATE_DISPLAYVIDEO_H
#define IMAGE_PROCESSING_TEMPLATE_DISPLAYVIDEO_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/utility.hpp>

#include <string>

class DisplayVideo {
private:
    std::string _fileSource;
    cv::VideoCapture *_videoCapture;
public:
    explicit DisplayVideo(std::string fileSource);
    void run();
    ~DisplayVideo();
};


#endif //IMAGE_PROCESSING_TEMPLATE_DISPLAYVIDEO_H
