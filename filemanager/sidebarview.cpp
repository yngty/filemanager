#include "sidebarview.h"

SideBarView::SideBarView(QWidget *parent)
    : DListView(parent)
{
    setVerticalScrollMode(ScrollPerPixel);
    setIconSize(QSize(16, 16));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
