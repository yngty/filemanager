#ifndef SIDEBARVIEW_H
#define SIDEBARVIEW_H

#include <DListView>

DWIDGET_USE_NAMESPACE

class SideBarView : public DListView
{
    Q_OBJECT
public:
    explicit SideBarView(QWidget *parent = nullptr);
};

#endif   // SIDEBARVIEW_H
