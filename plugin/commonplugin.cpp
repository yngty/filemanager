#include "commonplugin.h"
#include <QIcon>
#include <QUrl>
#include <QPair>
#include "sidebardefaultitemhandler.h"
#include "commoncrumbcontroller.h"

CommonPlugin::CommonPlugin(QObject *parent)
    : QObject(parent)
{
}

SideBarItem *CommonPlugin::createSideBarItem()
{
    SideBarItem *item = new SideBarItem(
            QIcon::fromTheme("user-home"),
            "主目录",
            QUrl::fromUserInput("/home/yngty"));

    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsDropEnabled);
    item->setRegisteredHandler(pluginName());
    return item;
}

SideBarInterfaceCreaterFunc CommonPlugin::createSideBarInterfaceTypeFunc()
{
    return SideBarInterfaceCreaterFunc(typeid(SideBarDefaultItemHandler).name(), [=]() { return new SideBarDefaultItemHandler(); });
}

QString CommonPlugin::pluginName()
{
    return "common";
}

CrumbCreaterFunc CommonPlugin::createCrumbCreaterTypeFunc()
{
    return CrumbCreaterFunc(typeid(CommonCrumbController).name(), [=]() { return new CommonCrumbController(); });
}
