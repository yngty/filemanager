#include "sidebarmanager.h"
#include "pluginmanager.h"

#include <QMultiHash>
#include <QDebug>

class SideBarManagerPrivate
{
public:
    explicit SideBarManagerPrivate(SideBarManager *qq);

    QMultiHash<const SideBarManager::KeyType, SideBarManager::SideBarInterfaceCreaterType> controllerCreatorHash;

    SideBarManager *q_ptr;
};

SideBarManagerPrivate::SideBarManagerPrivate(SideBarManager *qq)
    : q_ptr(qq)
{
}

SideBarManager *SideBarManager::instance()
{
    static SideBarManager manager;
    return &manager;
}

SideBarManager::SideBarManager(QObject *parent)
    : QObject(parent),
      d_private(new SideBarManagerPrivate(this))
{
    initSideBarItemHandlerFromPlugin();
}

SideBarManager::~SideBarManager()
{
}

bool SideBarManager::isRegisted(const QString &scheme, const std::type_info &info) const
{
    Q_D(const SideBarManager);

    const KeyType &key = KeyType(scheme);

    for (const SideBarInterfaceCreaterType &creator : d->controllerCreatorHash.values(key)) {
        if (creator.first == info.name())
            return true;
    }
    return false;
}

SideBarItemInterface *SideBarManager::createByIdentifier(const QString &identifier)
{
    Q_D(SideBarManager);
    KeyType key(identifier);

    const QList<SideBarInterfaceCreaterType> creators = d->controllerCreatorHash.values(key);
    if (creators.isEmpty())
        return nullptr;
    SideBarItemInterface *interface = creators.first().second();
    return interface;
}

void SideBarManager::insertToCreatorHash(const SideBarManager::KeyType &key, const SideBarManager::SideBarInterfaceCreaterType &creator)
{
    Q_D(SideBarManager);

    d->controllerCreatorHash.insert(key, creator);
}

void SideBarManager::initSideBarItemHandlerFromPlugin()
{
    qDebug() << "[PLUGIN]"
             << "try to load plugin of sidebar item handler";
    for (auto plugin : PluginManager::instance()->plugins()) {
        qWarning() << "[PLUGIN]"
                   << "load sidebar item handler from plugin:" << plugin.first;
        insertToCreatorHash(QString("%1").arg(plugin.first), plugin.second->createSideBarInterfaceTypeFunc());
    }
}
