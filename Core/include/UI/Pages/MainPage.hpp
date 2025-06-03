#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "PageAbstract.hpp"

#include <QVBoxLayout>
#include <QPushButton>

class MainPage : public PageAbstract {
    Q_OBJECT

private:
    QVBoxLayout *m_layout; 
    QPushButton *m_imageCameraButton;
public:

    explicit MainPage(QWidget *parent = nullptr){
        setupUI();
    };

    ~MainPage() {};

    void enterPage() override {

    }

    void leavePage() override {
        
    }

    void setupUI() override {
        QVBoxLayout *m_layout = new QVBoxLayout(this);

        m_layout->addWidget(m_imageCameraButton);
        m_layout->addStretch();

        setLayout(m_layout);
    }


};

#endif