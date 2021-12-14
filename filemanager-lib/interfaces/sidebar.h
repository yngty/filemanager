#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

class SideBarView;
class SideBarModel;
class SideBarItem;
class SideBarPrivate;
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
    ~SideBar() override;

    QWidget *view();

    void setCurrentUrl(const QUrl &url, bool changeUrl = true);

private slots:
    void onItemActivated(const QModelIndex &index);
    void onContextMenuRequested(const QPoint &pos);

private:
    void initUI();
    void initModelData();
    void initConnection();
    void appendItem(SideBarItem *item, const QString &groupName);
    int findItem(const QUrl &url, bool fuzzy = false) const;

    QScopedPointer<SideBarPrivate> d_private;
    Q_DECLARE_PRIVATE_D(d_private, SideBar)
};

#endif   // SIDEBAR_H
