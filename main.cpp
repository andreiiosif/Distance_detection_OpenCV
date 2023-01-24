#pragma ide diagnostic ignored "EndlessLoop"

#include "DisplayVideo.h"

int main()
{
    // Read video from file
    auto videoCapture = DisplayVideo("Video/impact.mp4");
    videoCapture.run();

    return 0;
}