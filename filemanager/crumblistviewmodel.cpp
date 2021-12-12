#include "crumblistviewmodel.h"

CrumbListviewModel::CrumbListviewModel(QObject *parent)
    : QStandardItemModel(parent)
{
}

void CrumbListviewModel::removeAll()
{
    removeRows(0, rowCount());
}

QModelIndex CrumbListviewModel::lastIndex()
{
    return index(rowCount() - 1, 0);
}
