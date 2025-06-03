#include <thread>

// #include "CameraSubscriber.hpp"
// #include "ImageProcessor.hpp"

#include "UI/MainWindow.hpp"

#include <QApplication>


int main(int argc, char **argv) {
    // CameraSubscriber subscriber("tcp://localhost:1883", "sensors/#");
    // subscriber.start();

    // ImageProcessor imageProcessor(subscriber);
    // std::thread process(&ImageProcessor::run, &imageProcessor);
    
    // process.join(); 

    QApplication a(argc, argv);
    MainWindow w;
    w.show();    
    return a.exec();
}
