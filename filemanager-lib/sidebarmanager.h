#ifndef SIDEBARMANAGER_H
#define SIDEBARMANAGER_H

#include <QObject>
#include <functional>

class SideBarItemInterface;
class SideBarManagerPrivate;
class SideBarManager : public QObject
{
    Q_OBJECT
    using KeyType = QString;
    using SideBarInterfaceCreaterType = QPair<QString, std::function<SideBarItemInterface *()>>;

public:
    static SideBarManager *instance();

    template<typename T>
    void registerSideBarInterface(const QString &identifier)
    {
        if (isRegisted<T>(identifier))
            return;
        insertToCreatorHash(KeyType(identifier), SideBarInterfaceCreaterType(typeid(T).name(), [=]() {
                                return new T();
                            }));
    }

    bool isRegisted(const QString &scheme, const std::type_info &info) const;

    template<typename T>
    bool isRegisted(const QString &scheme) const
    {
        return isRegisted(scheme, typeid(T));
    }

    SideBarItemInterface *createByIdentifier(const QString &identifier);

private:
    explicit SideBarManager(QObject *parent = nullptr);
    ~SideBarManager();
    void initSideBarItemHandlerFromPlugin();
    void insertToCreatorHash(const KeyType &key, const SideBarInterfaceCreaterType &creator);
    QScopedPointer<SideBarManagerPrivate> d_private;
    Q_DECLARE_PRIVATE_D(d_private, SideBarManager)
};

#endif   // SIDEBARMANAGER_H
