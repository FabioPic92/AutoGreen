#include "PageManager.hpp"

PageManager::PageManager(QStackedWidget *stackedWidget, QObject *parent) 
    : m_stackedWidget(stackedWidget)
{}

void PageManager::addPage(const QString &pageName, int pageIndex, PageAbstract *pageInstance){
    
}