#include "commonplugin.h"
#include <QIcon>
#include <QUrl>
#include <QPair>
#include "sidebarcommonitemhandler.h"
#include "commoncrumbcontroller.h"
#include "plugin2view.h"

CommonPlugin::CommonPlugin(QObject *parent)
    : QObject(parent)
{
}

ViewCreatorFunc CommonPlugin::createViewTypeFunc()
{
    return ViewCreatorFunc(typeid(Plugin2View).name(), [=]() { return new Plugin2View(); });
}

SideBarItem *CommonPlugin::createSideBarItem()
{
    SideBarItem *item = new SideBarItem(
            QIcon::fromTheme("user-desktop"),
            "插件2",
            QUrl::fromUserInput("plugin2:///"));

    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsDropEnabled);
    item->setRegisteredHandler(pluginName());
    return item;
}

SideBarInterfaceCreaterFunc CommonPlugin::createSideBarInterfaceTypeFunc()
{
    return SideBarInterfaceCreaterFunc(typeid(SideBarCommonItemHandler).name(), [=]() { return new SideBarCommonItemHandler(); });
}

QString CommonPlugin::pluginName()
{
    return "plugin2";
}

CrumbCreaterFunc CommonPlugin::createCrumbCreaterTypeFunc()
{
    return CrumbCreaterFunc(typeid(CommonCrumbController).name(), [=]() { return new CommonCrumbController(); });
}
