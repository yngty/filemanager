#ifndef COMMONPLUGIN_H
#define COMMONPLUGIN_H

#include <QObject>

#include <interfaces/plugininterface.h>

class CommonPlugin : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.deepin.filemanager.PluginInterface_iid" FILE "plugin2.json")
    Q_INTERFACES(PluginInterface)
public:
    explicit CommonPlugin(QObject *parent = nullptr);

public:
    virtual ViewCreatorFunc createViewTypeFunc() override;
    virtual SideBarItem *createSideBarItem() override;
    virtual SideBarInterfaceCreaterFunc createSideBarInterfaceTypeFunc() override;
    virtual CrumbCreaterFunc createCrumbCreaterTypeFunc() override;
    virtual QString pluginName() override;
};

#endif   // COMMONPLUGIN_H
