#ifndef PAGE_ABSTRACT_H
#define PAGE_ABSTRACT_H

#include <QWidget>

class PageAbstract : public QWidget {
    Q_OBJECT
public:
    explicit PageAbstract(QWidget *parent = nullptr){};
    virtual ~PageAbstract() = default;

    virtual void enterPage() = 0;
    virtual void leavePage() = 0;
    virtual void setupUI() = 0;

};


#endif
