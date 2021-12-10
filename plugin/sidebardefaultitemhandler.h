#ifndef SIDEBARDEFAULTITEMHANDLER_H
#define SIDEBARDEFAULTITEMHANDLER_H

#include "interfaces/sidebariteminterface.h"

#include <QObject>

class SideBarDefaultItemHandler : public QObject, public SideBarItemInterface
{

    Q_GADGET
public:
    SideBarDefaultItemHandler(QObject *parent = nullptr);

    virtual void cdAction() override;

    virtual QMenu *contextMenu(const SideBarItem *item) override;
};

#endif   // SIDEBARDEFAULTITEMHANDLER_H
