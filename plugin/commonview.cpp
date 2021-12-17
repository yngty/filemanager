#include "commonview.h"

#include <QHBoxLayout>

#include <QLabel>

Plugin2View::Plugin2View()
    : QWidget()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QLabel *label = new QLabel(tr("common center"), this);
    layout->addWidget(label);

    setLayout(layout);
}

Plugin2View::~Plugin2View()
{
}

QWidget *Plugin2View::widget() const
{
    return static_cast<QWidget *>(const_cast<Plugin2View *>(this));
}

QUrl Plugin2View::rootUrl() const
{
    return QUrl();
}

BaseView::ViewState Plugin2View::viewState() const
{
    return BaseView::ViewState::ViewIdle;
}

bool Plugin2View::setRootUrl(const QUrl &url)
{
    return true;
}

QList<QAction *> Plugin2View::toolBarActionList() const
{
    return QList<QAction *>();
}

void Plugin2View::refresh()
{
}
