#ifndef CRUMBLISTVIEWMODEL_H
#define CRUMBLISTVIEWMODEL_H

#include <QStandardItemModel>

class CrumbListviewModel : public QStandardItemModel
{
public:
    enum Roles {
        FileUrlRole = Qt::UserRole + 1
    };
    Q_ENUM(Roles)

    explicit CrumbListviewModel(QObject *parent = nullptr);

    void removeAll();
    QModelIndex lastIndex();
};

#endif   // CRUMBLISTVIEWMODEL_H
