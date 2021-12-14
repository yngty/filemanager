#include "windowmanager.h"
#include "filemanagerwindow.h"

#include <QHash>
#include <QUrl>

class WindowManagerPrivate
{

public:
    explicit WindowManagerPrivate(WindowManager *qq)
        : q_ptr(qq) {}

private:
    QHash<quint64, FileManagerWindow *> windows;
    WindowManager *q_ptr;
};

WindowManager *WindowManager::instance()
{
    static WindowManager manager;
    return &manager;
}

WindowManager::~WindowManager()
{
}

WindowManager::WindowManager(QObject *parent)
    : QObject(parent),
      d_private(new WindowManagerPrivate(this))
{
}

void WindowManager::showNewWindow(const QUrl &url, const bool &isNewWindow)
{
    if (url.isEmpty() || !url.isValid())
        return;
    if (isNewWindow) {
    } else {
    }
}
