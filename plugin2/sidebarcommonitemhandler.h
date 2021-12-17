#ifndef SideBarCommonItemHandler_H
#define SideBarCommonItemHandler_H

#include "interfaces/sidebariteminterface.h"

class SideBarCommonItemHandler : public SideBarItemInterface
{
public:
    SideBarCommonItemHandler(QObject *parent = nullptr);

    virtual QMenu *contextMenu(const SideBarItem *item) override;
};

#endif   // SideBarCommonItemHandler_H
