#include "baseview.h"
#include "filemanagerwindow.h"

#include <QAction>

BaseView::BaseView()
{
}

BaseView::~BaseView()
{
}

void BaseView::deleteLater()
{
    if (QObject *obj = dynamic_cast<QObject *>(this))
        return obj->deleteLater();

    delete this;
}

BaseView::ViewState BaseView::viewState() const
{
    return ViewIdle;
}

QList<QAction *> BaseView::toolBarActionList() const
{
    return QList<QAction *>();
}

void BaseView::refresh()
{
}

void BaseView::notifyUrlChanged()
{
    if (FileManagerWindow *w = qobject_cast<FileManagerWindow *>(widget()->window())) {
        w->currentUrlChanged();
    }
}

void BaseView::notifyStateChanged()
{
    if (FileManagerWindow *w = qobject_cast<FileManagerWindow *>(widget()->window())) {
        w->currentViewStateChanged();
    }
}

void BaseView::requestCdTo(const QUrl &url)
{
    if (FileManagerWindow *w = qobject_cast<FileManagerWindow *>(widget()->window())) {
        w->cdForTabByView(this, url);
    }
}

void BaseView::notifySelectUrlChanged(const QList<QUrl> &urlList)
{
    if (FileManagerWindow *w = qobject_cast<FileManagerWindow *>(widget()->window())) {
        emit w->selectUrlChanged(urlList);
    }
}
