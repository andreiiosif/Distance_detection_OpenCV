#pragma ide diagnostic ignored "EndlessLoop"

#include "DisplayVideo.h"

int main()
{
    // Open a video and play on a window
    DisplayVideo displayVideo("Video/impact.mp4");
    displayVideo.run();

    return 0;
}