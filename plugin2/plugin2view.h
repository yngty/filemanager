#ifndef COMMONVIEW_H
#define COMMONVIEW_H

#include "interfaces/baseview.h"

#include <QWidget>

class Plugin2View : public QWidget, public BaseView
{
    Q_OBJECT
public:
    Plugin2View();
    ~Plugin2View() override;

public:
    virtual QWidget *widget() const override;
    virtual QUrl rootUrl() const override;
    virtual ViewState viewState() const override;
    virtual bool setRootUrl(const QUrl &url) override;
    virtual QList<QAction *> toolBarActionList() const override;
    virtual void refresh() override;
};

#endif   // COMMONVIEW_H
