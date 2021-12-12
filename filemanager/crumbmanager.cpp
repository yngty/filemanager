#include "crumbmanager.h"
#include "pluginmanager.h"

#include <QMultiHash>
#include <QDebug>

class CrumbManagerPrivate
{
public:
    explicit CrumbManagerPrivate(CrumbManager *qq);

    QMultiHash<const CrumbManager::KeyType, CrumbManager::CrumbCreaterType> controllerCreatorHash;

    CrumbManager *q_ptr;
};

CrumbManagerPrivate::CrumbManagerPrivate(CrumbManager *qq)
    : q_ptr(qq)
{
}

CrumbManager::CrumbManager(QObject *parent)
    : QObject(parent), d_ptr(new CrumbManagerPrivate(this))
{
    initCrumbControllerFromPlugin();
}

CrumbManager::~CrumbManager()
{
}
CrumbManager *CrumbManager::instance()
{
    static CrumbManager manager;

    return &manager;
}

bool CrumbManager::isRegisted(const QString &scheme, const std::type_info &info) const
{
    Q_D(const CrumbManager);

    const KeyType &type = KeyType(scheme);

    foreach (const CrumbCreaterType &value, d->controllerCreatorHash.values(type)) {
        if (value.first == info.name())
            return true;
    }

    return false;
}

CrumbInterface *CrumbManager::createControllerByUrl(const QUrl &url, CrumbBar *crumbBar) const
{
    Q_D(const CrumbManager);
    KeyType key = url.scheme();

    const QList<CrumbCreaterType> creatorList = d->controllerCreatorHash.values(key);

    Q_CHECK_PTR(crumbBar);
    if (!creatorList.isEmpty()) {
        CrumbInterface *i = (creatorList.first().second)();
        i->setCrumbBar(crumbBar);
        return i;
    }

    return nullptr;
}

void CrumbManager::insertToCreatorHash(const CrumbManager::KeyType &key, const CrumbManager::CrumbCreaterType &creator)
{
    Q_D(CrumbManager);

    d->controllerCreatorHash.insertMulti(key, creator);
}

void CrumbManager::initCrumbControllerFromPlugin()
{
    qWarning() << "[PLUGIN]"
               << "try to load plugin of crumb controller";
    auto plugins = PluginManager::instance()->plugins();
    for (auto plugin : plugins) {
        qWarning() << "[PLUGIN]"
                   << "load crumb controller from plugin:" << plugin.first;
        insertToCreatorHash(plugin.first, plugin.second->createCrumbCreaterTypeFunc());
    }
}
