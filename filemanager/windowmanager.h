#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>

class WindowManagerPrivate;
class WindowManager : public QObject
{
    Q_OBJECT
public:
    static WindowManager *instance();
    ~WindowManager() override;

    void showNewWindow(const QUrl &url, const bool &isNewWindow = false);

protected:
    explicit WindowManager(QObject *parent = nullptr);

private:
    QScopedPointer<WindowManagerPrivate> d_private;
    Q_DECLARE_PRIVATE_D(d_private, WindowManager)
};

#endif   // WINDOWMANAGER_H
