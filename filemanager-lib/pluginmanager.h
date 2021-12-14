#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "interfaces/plugininterface.h"
#include <QObject>
#include <QList>
#include <QPair>

#define SIDEBAR_ID_INTERNAL_FALLBACK "__internal"

using PluginList = QList<QPair<QString, PluginInterface *>>;
using PluginPathList = QList<QPair<QString, QString>>;

class PluginManager : public QObject
{
    Q_OBJECT
public:
    static PluginManager *instance();

    QString pluginDir();
    void loadPlugin();
    void unloadPlugin(const QString &name);
    PluginList plugins();

private:
    explicit PluginManager(QObject *parent = nullptr);
    PluginList pluginList;
    PluginPathList pluginPahtList;
};

#endif   // PLUGINMANAGER_H
