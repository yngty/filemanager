#include "sidebarcommonitemhandler.h"
#include "interfaces/sidebar.h"
#include "interfaces/sidebaritem.h"

#include <QDebug>
#include <QMenu>

SideBarCommonItemHandler::SideBarCommonItemHandler(QObject *parent)
    : SideBarItemInterface(parent)
{
}

QMenu *SideBarCommonItemHandler::contextMenu(const SideBarItem *item)
{
    QMenu *menu = new QMenu;
    menu->addAction(QObject::tr("Open in new window"), [item]() {
        qDebug() << "Open in new window";
    });
    return menu;
}
