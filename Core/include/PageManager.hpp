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
};

class PageManager : public QWidget, public BaseStateMachine{
    Q_OBJECT
public:
    explicit PageManager(QStackedWidget *stackedWidget, QObject *parent = nullptr);
    ~PageManager() = default;

    void setup() override {

    }

    void addPage(const QString &pageName, int pageIndex, PageAbstract *pageInstance);

private:
    QStackedWidget *m_stackedWidget;
    QMap<AppState, PageAbstract*> m_pages;
    QMap<AppState, int> m_pageIndices; 
};

#endif