#include "PageManager.hpp"

PageManager::PageManager(QStackedWidget *stackedWidget, QObject *parent) 
    : m_stackedWidget(stackedWidget)
{
    MainPage *mainPage = new MainPage(m_stackedWidget);
    int mainPageIndex = m_stackedWidget->addWidget(mainPage);

    m_pages[AppState::MAIN] = mainPage;
    m_pageIndices[AppState::MAIN] = mainPageIndex;

}


void PageManager::setCurrentState(AppState newState) {
    qDebug() << "PageManager: Attempting to set state to " << static_cast<int>(newState);

    if (m_pages.contains(m_currentState) && m_pages[m_currentState]) {
        m_pages[m_currentState]->leavePage();
    }

    m_currentState = newState;

    if (m_pageIndices.contains(newState)) {
        int indexToDisplay = m_pageIndices[newState];
        m_stackedWidget->setCurrentIndex(indexToDisplay);
        qDebug() << "PageManager: Switched QStackedWidget to index " << indexToDisplay;
    } else {
        qWarning() << "PageManager: Attempted to set an unknown state: " << static_cast<int>(newState);
    }

    if (m_pages.contains(newState) && m_pages[newState]) {
        m_pages[newState]->enterPage();
    }
}

void PageManager::TakePhoto() {
     qDebug() << "TakePhoto";
}
