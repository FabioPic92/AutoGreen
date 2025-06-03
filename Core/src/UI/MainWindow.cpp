#include "UI/MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Finestra Vuota di Test Qt");
    resize(800, 600);

}

MainWindow::~MainWindow() {
}

void MainWindow::setupMainWindow() {
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);    

    m_pageManager = new PageManager(m_stackedWidget);
    m_pageManager->setup();
}
