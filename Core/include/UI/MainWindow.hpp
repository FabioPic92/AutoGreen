#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStackedWidget> 

#include "UI/Pages/MainPage.hpp"
#include "PageManager.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT 
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setupMainWindow();

private:

    QStackedWidget *m_stackedWidget;

    PageManager *m_pageManager;

    MainPage *m_mainPage;
};

#endif 
