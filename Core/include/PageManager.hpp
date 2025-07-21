#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include "BaseStateMachine.hpp"

#include <QWidget>
#include <QObject>
#include <QMap>
#include <QStackedWidget>

#include "UI/Pages/MainPage.hpp"

enum class AppState {
    NONE,
    MAIN,
    SETTINGS
};

class PageManager : public QWidget, public BaseStateMachine {
    Q_OBJECT
public:
    explicit PageManager(QStackedWidget *stackedWidget, QObject *parent = nullptr);
    ~PageManager() = default;

    void setup() override {
        setCurrentState(AppState::MAIN); // Questo farà sì che la MainPage sia mostrata all'avvio
        qDebug() << "PageManager: setup() complete. Initial state set to MAIN.";
    }


    void setCurrentState(AppState newState);

private:
    QStackedWidget *m_stackedWidget;
    QMap<AppState, PageAbstract*> m_pages;
    QMap<AppState, int> m_pageIndices; 

    AppState m_currentState = AppState::NONE;

private slots:
    void TakePhoto();
};

#endif