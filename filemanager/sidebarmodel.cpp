#include "sidebarmodel.h"
#include "interfaces/sidebaritem.h"

SideBarModel::SideBarModel(QObject *parent)
    : QStandardItemModel(parent)
{
}

SideBarItem *SideBarModel::itemFromIndex(const QModelIndex &index) const
{
    QStandardItem *item = QStandardItemModel::itemFromIndex(index);
    SideBarItem *castedItem = static_cast<SideBarItem *>(item);

    return castedItem;
}

SideBarItem *SideBarModel::itemFromIndex(int index) const
{
    return itemFromIndex(this->index(index, 0));
}
