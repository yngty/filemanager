#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QUrl>

class QWidget;
class QAction;
class BaseView
{
public:
    enum ViewState {
        ViewBusy,
        ViewIdle
    };

    BaseView();
    virtual ~BaseView();

    void deleteLater();

    virtual QWidget *widget() const = 0;
    virtual QUrl rootUrl() const = 0;
    virtual ViewState viewState() const;
    virtual bool setRootUrl(const QUrl &url) = 0;
    virtual QList<QAction *> toolBarActionList() const;
    virtual void refresh();

protected:
    void notifyUrlChanged();
    void notifyStateChanged();
    void requestCdTo(const QUrl &url);
    void notifySelectUrlChanged(const QList<QUrl> &urlList);
};

#endif   // BASEVIEW_H
