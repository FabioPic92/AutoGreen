#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "CameraSubscriber.hpp"

class ImageProcessor {
public:
    ImageProcessor(CameraSubscriber& subscriber);
    void run();

private:
    CameraSubscriber &m_subscriber;
};

#endif