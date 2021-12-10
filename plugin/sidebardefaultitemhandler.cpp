#include "sidebardefaultitemhandler.h"
#include "interfaces/sidebar.h"
#include "interfaces/sidebaritem.h"

#include <QDebug>
#include <QMenu>

SideBarDefaultItemHandler::SideBarDefaultItemHandler(QObject *parent)
    : QObject(parent)
{
}

void SideBarDefaultItemHandler::cdAction()
{
    qDebug() << "common plugin do cd Action";
}

QMenu *SideBarDefaultItemHandler::contextMenu(const SideBarItem *item)
{
    QMenu *menu = new QMenu;
    menu->addAction(QObject::tr("Open in new window"), [item]() {
        qDebug() << "Open in new window";
    });
    return menu;
}
