#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "CameraSubscriber.hpp"

#include <QObject>   
#include <QThread>
#include <vector> 
#include <string> 
#include <atomic>   

class ImageProcessor {
    Q_OBJECT
public:
    explicit ImageProcessor(CameraSubscriber& subscriber, QObject* parent = nullptr);

public slots:
    void run();

public:
    void stop();

signals:
    void imageSaved(const QString& filename);

    void imageReadyForDisplay(const std::vector<uint8_t>& imageData);

    void finished();    

private:
    CameraSubscriber &m_subscriber;
    std::atomic<bool> m_stopFlag;         
    int m_imageCounter;          
};

#endif