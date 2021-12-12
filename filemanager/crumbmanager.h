#ifndef CRUMBMANAGER_H
#define CRUMBMANAGER_H

#include <QObject>
#include <functional>

class CrumbBar;
class CrumbInterface;
class CrumbManagerPrivate;
class CrumbManager : public QObject
{
    Q_OBJECT

    using KeyType = QString;
    using CrumbCreaterType = QPair<QString, std::function<CrumbInterface *()>>;

public:
    static CrumbManager *instance();
    template<class T>
    void dRegisterCrumbCreator(const QString &scheme)
    {
        if (isRegisted<T>(scheme))
            return;

        insertToCreatorHash(KeyType(scheme), CrumbCreaterType(typeid(T).name(), [=]() {
                                return static_cast<CrumbInterface *>(new T());
                            }));
    }

    bool isRegisted(const QString &scheme, const std::type_info &info) const;

    template<class T>
    bool isRegisted(const QString &scheme) const
    {
        return isRegisted(scheme, typeid(T));
    }

    CrumbInterface *createControllerByUrl(const QUrl &url, CrumbBar *crumbBar) const;

private:
    explicit CrumbManager(QObject *parent = nullptr);
    ~CrumbManager();

    void initCrumbControllerFromPlugin();
    void insertToCreatorHash(const KeyType &key, const CrumbCreaterType &creator);

    QScopedPointer<CrumbManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(CrumbManager)
};

#endif   // CRUMBMANAGER_H
