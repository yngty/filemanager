#ifndef SIDEBARITEMINTERFACE_H
#define SIDEBARITEMINTERFACE_H

#include <QObject>

class QMenu;
class SideBar;
class SideBarItem;
class SideBarItemInterface : public QObject
{
    Q_GADGET
public:
    explicit SideBarItemInterface(QObject *parent = nullptr);
    virtual ~SideBarItemInterface();
    virtual void cdAction(const SideBar *sidebar, const SideBarItem *item);
    virtual QMenu *contextMenu(const SideBarItem *item) = 0;
};

#endif   // SIDEBARITEMINTERFACE_H
