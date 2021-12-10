#ifndef SIDEBARMODEL_H
#define SIDEBARMODEL_H

#include <QStandardItemModel>

class SideBarItem;
class SideBarModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit SideBarModel(QObject *parent = nullptr);

    SideBarItem *itemFromIndex(const QModelIndex &index) const;

    SideBarItem *itemFromIndex(int index) const;

signals:

public slots:
};

#endif   // SIDEBARMODEL_H
