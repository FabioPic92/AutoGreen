
#include "ImageProcessor.hpp"

#include <iostream>
#include <fstream>

ImageProcessor::ImageProcessor(CameraSubscriber& subscriber)
    : m_subscriber(subscriber) {}

void ImageProcessor::run() {
    std::vector<uint8_t> imageBuffer;
    int imageCounter = 0;

    while (true) {
        std::pair<std::string, std::vector<uint8_t>> msg;

        if (m_subscriber.get_next_message(msg)) {
            const auto& payload = msg.second;

            if (payload.size() == 3 &&
                payload[0] == 'E' &&
                payload[1] == 'O' &&
                payload[2] == 'F') {

                std::string filename = "image_" + std::to_string(imageCounter++) + ".jpg";
                std::ofstream out(filename, std::ios::binary);
                out.write(reinterpret_cast<const char*>(imageBuffer.data()), imageBuffer.size());
                out.close();

                std::cout << "Image saved: " << filename << std::endl;

                imageBuffer.clear();
            } else {
                imageBuffer.insert(imageBuffer.end(), payload.begin(), payload.end());
            }
        }
    }
}