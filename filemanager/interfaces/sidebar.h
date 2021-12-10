#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

class SideBarView;
class SideBarModel;
class SideBarItem;
class SideBar : public QWidget
{
    Q_OBJECT
public:
    enum SideBarEdge {
        SIDEBAR_MINIMUMWIDTH = 120,
        SIDEBAR_MAXIMUMWIDTH = 200
    };

    enum GroupName {
        Common,
        Device,
        Bookmark,
        Network,
        Tag,
        Other,
        Plugin,
        Unknow
    };

    explicit SideBar(QWidget *parent = nullptr);
    ~SideBar() = default;

    QWidget *view();
private slots:
    void onItemActivated(const QModelIndex &index);
    void onContextMenuRequested(const QPoint &pos);

private:
    void initUI();
    void initModelData();
    void initConnection();
    void appendItem(SideBarItem *item, const QString &groupName);

    SideBarView *sidebarView;
    SideBarModel *sidebarModel;
};

#endif   // SIDEBAR_H
