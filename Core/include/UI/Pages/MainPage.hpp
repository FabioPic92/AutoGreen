#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "PageAbstract.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include "CameraPublisher.hpp"
#include "CameraSubscriber.hpp"

class MainPage : public PageAbstract {
    Q_OBJECT

private:
    QVBoxLayout *m_layout; 
    QPushButton *m_imageCameraButton;

    CameraPublisher *m_publisher; 
    CameraSubscriber *m_subscriber;
public:
    MainPage(QWidget *parent = nullptr);

    ~MainPage() {};

    void enterPage() override {

    }

    void leavePage() override {
        
    }

    void setupUI() override {
        QVBoxLayout *m_layout = new QVBoxLayout(this);

        m_imageCameraButton = new QPushButton("Take Photo", this); 

        m_layout->addWidget(m_imageCameraButton);
        m_layout->addStretch();

        setLayout(m_layout);

        connect(m_imageCameraButton, &QPushButton::clicked, this, &MainPage::onMyNewButtonClicked);
    }

private slots:
    void onMyNewButtonClicked();

signals:
    void photoClicked(); 

};

#endif