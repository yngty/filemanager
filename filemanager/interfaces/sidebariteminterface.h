#ifndef SIDEBARITEMINTERFACE_H
#define SIDEBARITEMINTERFACE_H

#include <QObject>

class QMenu;
class SideBarItem;
class SideBarItemInterface
{
public:
    virtual ~SideBarItemInterface() = default;
    virtual void cdAction() = 0;
    virtual QMenu *contextMenu(const SideBarItem *item) = 0;
};

#endif   // SIDEBARITEMINTERFACE_H
