#include <thread>

#include "UI/MainWindow.hpp"

#include <QApplication>


int main(int argc, char **argv) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setupMainWindow();
    w.show();    
    return a.exec();
}
