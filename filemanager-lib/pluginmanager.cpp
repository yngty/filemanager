#include "pluginmanager.h"

#include <QPluginLoader>
#include <QString>
#include <QDir>
#include <QDebug>

PluginManager::PluginManager(QObject *parent)
    : QObject(parent)
{
}

PluginManager *PluginManager::instance()
{
    static PluginManager manager;
    return &manager;
}

QString PluginManager::pluginDir()
{
    return QString("/home/yngty/Workspace/uos/build-filemanager-unknown-Debug/");
}

void PluginManager::loadPlugin()
{

    qDebug() << pluginDir();
    QDir dir(pluginDir());
    qWarning() << dir.entryList(QDir::Files);
    for (auto pluginFile : dir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(dir.absoluteFilePath(pluginFile));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            PluginInterface *pluginInterface = qobject_cast<PluginInterface *>(plugin);
            if (pluginInterface) {
                QString pluginName = pluginInterface->pluginName();
                pluginList << qMakePair<QString, PluginInterface *>(pluginName, pluginInterface);
                pluginPahtList << qMakePair<QString, QString>(pluginName, dir.absoluteFilePath(pluginFile));
                qInfo() << "plugin name:" << pluginName;
                qInfo() << "plugin path:" << dir.absoluteFilePath(pluginFile);
            }
        } else {
            qInfo() << pluginLoader.errorString();
        }
    }
}

void PluginManager::unloadPlugin(const QString &name)
{
    Q_UNUSED(name);
}

PluginList PluginManager::plugins()
{
    return pluginList;
}
