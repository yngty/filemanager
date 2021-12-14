#ifndef SIDEBARITEM_H
#define SIDEBARITEM_H

#include <DStandardItem>
#include <QUrl>

DWIDGET_USE_NAMESPACE

class SideBarItem : public DStandardItem
{
public:
    enum Roles {
        ItemTypeRole = Dtk::UserRole + 1,
        ItemUrlRole,
        ItemGroupNameRole,
        ItemUseRegisteredHandlerRole,
        ItemUniqueKeyRole,
        ItemVolTagRole,
        ItemUserCustomRole = Dtk::UserRole + 0x0100
    };

    enum ItemTypes {
        SidebarItem,
        Separator
    };

    explicit SideBarItem(const QIcon &icon, const QString &text, const QUrl &url = QUrl(), const QString &groupName = "default");

    explicit SideBarItem(const QUrl &url = QUrl(), const QString &groupName = "default");

    QString groupName() const;
    QUrl url() const;
    int itemType() const;
    bool useRegisteredHandler() const;

    void setUrl(const QUrl &url);
    void setGroupName(const QString &groupName);
    void setRegisteredHandler(const QString &identifier);

    QString registeredHandler(const QString &fallback = QString()) const;

    constexpr static int SidebarItemType = QStandardItem::UserType + 1;
};

#endif   // SIDEBARITEM_H
