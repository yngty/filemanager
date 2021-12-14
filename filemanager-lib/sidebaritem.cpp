#include "interfaces/sidebaritem.h"
#include <QUuid>

SideBarItem::SideBarItem(const QIcon &icon, const QString &text, const QUrl &url, const QString &groupName)
    : DStandardItem(icon, text)
{
    setUrl(url);
    setGroupName(groupName);
    this->setData(SidebarItem, ItemTypeRole);
    this->setData("none", ItemUseRegisteredHandlerRole);
    this->setData(QUuid::createUuid().toString(), ItemUniqueKeyRole);
    this->setData(url.path().remove("/").remove(".localdisk"), ItemVolTagRole);
}

SideBarItem::SideBarItem(const QUrl &url, const QString &groupName)
    : SideBarItem(QIcon(), QString(), url, groupName)
{
}

QString SideBarItem::groupName() const
{
    return this->data(ItemGroupNameRole).toString();
}

QUrl SideBarItem::url() const
{
    return this->data(ItemUrlRole).value<QUrl>();
}

void SideBarItem::setUrl(const QUrl &url)
{
    this->setData(QVariant::fromValue(url), ItemUrlRole);
}

void SideBarItem::setGroupName(const QString &groupName)
{
    this->setData(groupName, ItemGroupNameRole);
}

void SideBarItem::setRegisteredHandler(const QString &identifier)
{
    this->setData(identifier, ItemUseRegisteredHandlerRole);
}

bool SideBarItem::useRegisteredHandler() const
{
    return this->registeredHandler() == "none";
}

QString SideBarItem::registeredHandler(const QString &fallback) const
{
    QString identifier = this->data(ItemUseRegisteredHandlerRole).toString();
    if (identifier != "none") {
        return identifier;
    } else {
        return identifier.isEmpty() ? fallback : identifier;
    }
}

int SideBarItem::itemType() const
{
    return this->data(ItemTypeRole).toInt();
}
