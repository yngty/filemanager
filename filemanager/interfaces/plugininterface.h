#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include "sidebariteminterface.h"
#include "crumbinterface.h"
#include "sidebaritem.h"

#include <QString>
#include <QPair>
#include <functional>

using SideBarInterfaceCreaterFunc = QPair<QString, std::function<SideBarItemInterface *()>>;
using CrumbCreaterFunc = QPair<QString, std::function<CrumbInterface *()>>;

class PluginInterface
{
public:
    virtual ~PluginInterface() = default;

    virtual SideBarItem *createSideBarItem() = 0;

    virtual SideBarInterfaceCreaterFunc createSideBarInterfaceTypeFunc() = 0;

    virtual CrumbCreaterFunc createCrumbCreaterTypeFunc() = 0;

    virtual QString pluginName() = 0;
};
QT_BEGIN_NAMESPACE

#define MYPluginInterface_iid "com.deepin.filemanager.PluginInterface_iid"

Q_DECLARE_INTERFACE(PluginInterface, MYPluginInterface_iid)
QT_END_NAMESPACE

#endif   // PLUGININTERFACE_H
