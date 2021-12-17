#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QObject>

#include <functional>

class BaseView;
class ViewManagerPrivate;
class ViewManager : public QObject
{
    Q_OBJECT
    using KeyType = QPair<QString, QString>;
    using ViewCreatorType = QPair<QString, std::function<BaseView *()>>;

public:
    static ViewManager *instance();

    explicit ViewManager(QObject *parent = nullptr);
    ~ViewManager();

    template<class T>
    void dRegisterUrlView(const QString &scheme, const QString &host)
    {
        if (isRegisted<T>(scheme, host))
            return;

        insertToCreatorHash(KeyType(scheme, host), ViewCreatorType(typeid(T).name(), [=]() {
                                return new T();
                            }));
    }
    bool isRegisted(const QString &scheme, const QString &host, const std::type_info &info) const;
    template<class T>
    bool isRegisted(const QString &scheme, const QString &host) const
    {
        return isRegisted(scheme, host, typeid(T));
    }

    BaseView *createViewByUrl(const QUrl &fileUrl) const;

private:
    void initViewFromPlugin();
    void insertToCreatorHash(const ViewManager::KeyType &key, const ViewManager::ViewCreatorType &creator);

private:
    QScopedPointer<ViewManagerPrivate> d_private;
    Q_DECLARE_PRIVATE_D(d_private, ViewManager)
};

#endif   // VIEWMANAGER_H
