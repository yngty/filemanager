#include "viewmanager.h"
#include "pluginmanager.h"

#include <QMultiHash>
#include <QDebug>

class ViewManagerPrivate
{

public:
    explicit ViewManagerPrivate(ViewManager *qq)
        : q_ptr(qq) {}
    QMultiHash<const ViewManager::KeyType, ViewManager::ViewCreatorType> controllerCreatorHash;

private:
    ViewManager *q_ptr { nullptr };
};

ViewManager *ViewManager::instance()
{
    static ViewManager manager;
    return &manager;
}

ViewManager::ViewManager(QObject *parent)
    : QObject(parent),
      d_private(new ViewManagerPrivate(this))
{
    initViewFromPlugin();
}

ViewManager::~ViewManager()
{
}

bool ViewManager::isRegisted(const QString &scheme, const QString &host, const std::type_info &info) const
{
    Q_D(const ViewManager);

    const KeyType &key = KeyType(scheme, host);
    auto values = d->controllerCreatorHash.values(key);
    auto ret = std::any_of(values.begin(), values.end(), [&info](const ViewCreatorType &value) {
        return value.first == info.name();
    });

    return ret;
}

BaseView *ViewManager::createViewByUrl(const QUrl &fileUrl) const
{
    Q_D(const ViewManager);
    QList<KeyType> handlerTypeList;

    handlerTypeList << KeyType(fileUrl.scheme(), fileUrl.host());
    handlerTypeList << KeyType(QString(), fileUrl.host());
    handlerTypeList << KeyType(fileUrl.scheme(), QString());

    for (const KeyType &handlerType : handlerTypeList) {
        const QList<ViewCreatorType> creatorList = d->controllerCreatorHash.values(handlerType);

        if (!creatorList.isEmpty()) {
            return (creatorList.first().second)();
        }
    }
    return nullptr;
}

void ViewManager::initViewFromPlugin()
{
    qDebug() << "[PLUGIN]"
             << "try to load plugin of view";
    for (auto plugin : PluginManager::instance()->plugins()) {
        qDebug() << "[PLUGIN]"
                 << "load view from plugin:" << plugin.first;
        insertToCreatorHash(KeyType("common", ""), plugin.second->createViewTypeFunc());
    }
}

void ViewManager::insertToCreatorHash(const ViewManager::KeyType &key, const ViewManager::ViewCreatorType &creator)
{
    Q_D(ViewManager);

    d->controllerCreatorHash.insertMulti(key, creator);
}
