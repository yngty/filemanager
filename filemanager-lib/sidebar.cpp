#include "interfaces/sidebar.h"
#include "interfaces/sidebaritem.h"
#include "sidebarview.h"
#include "sidebarmodel.h"
#include "sidebaritemdelegate.h"
#include "sidebarmanager.h"
#include "pluginmanager.h"

#include <QScrollBar>
#include <QVBoxLayout>
#include <QMenu>

class SideBarPrivate
{
public:
    explicit SideBarPrivate(SideBar *qq)
        : sidebarView(new SideBarView(qq)),
          sidebarModel(new SideBarModel(qq)),
          q_ptr(qq)

    {
    }

private:
    QUrl currentUrl;
    SideBarView *sidebarView;
    SideBarModel *sidebarModel;

    SideBar *q_ptr;
    Q_DECLARE_PUBLIC(SideBar)
};

SideBar::SideBar(QWidget *parent)
    : QWidget(parent),
      d_private(new SideBarPrivate(this))
{
    initUI();
    initModelData();
    initConnection();
}

SideBar::~SideBar()
{
}

QWidget *SideBar::view()
{
    Q_D(SideBar);
    return d->sidebarView;
}

void SideBar::setCurrentUrl(const QUrl &url, bool changeUrl)
{
    Q_D(SideBar);

    d->currentUrl = changeUrl ? url : d->currentUrl;

    int index = findItem(d->currentUrl, true);
    if (index != -1) {
        d->sidebarView->setCurrentIndex(d->sidebarModel->index(index, 0));
    } else {
        d->sidebarView->clearSelection();
    }
}

void SideBar::onItemActivated(const QModelIndex &index)
{
    Q_D(SideBar);

    SideBarItem *item = d->sidebarModel->itemFromIndex(index);

    QString identifierStr = item->registeredHandler();

    QScopedPointer<SideBarItemInterface> interface(SideBarManager::instance()->createByIdentifier(identifierStr));
    if (interface) {
        interface->cdAction(this, item);
    }
}

void SideBar::onContextMenuRequested(const QPoint &pos)
{
    Q_D(SideBar);

    QModelIndex modelIndex = d->sidebarView->indexAt(pos);
    if (!modelIndex.isValid()) {
        return;
    }

    SideBarItem *item = d->sidebarModel->itemFromIndex(modelIndex);

    QString identifierStr = item->registeredHandler(SIDEBAR_ID_INTERNAL_FALLBACK);

    QScopedPointer<SideBarItemInterface> interface(SideBarManager::instance()->createByIdentifier(identifierStr));
    QMenu *menu = nullptr;
    if (interface) {
        menu = interface->contextMenu(item);
        if (menu) {
            menu->exec(this->mapToGlobal(pos));
        }
    }
}

void SideBar::initUI()
{
    Q_D(SideBar);
    d->sidebarView->setModel(d->sidebarModel);
    d->sidebarView->setItemDelegate(new SideBarItemDelegate(d->sidebarView));
    d->sidebarView->setViewportMargins(10, 0, d->sidebarView->verticalScrollBar()->sizeHint().width(), 0);
    d->sidebarView->setContextMenuPolicy(Qt::CustomContextMenu);
    d->sidebarView->setFrameShape(QFrame::Shape::NoFrame);
    d->sidebarView->setAutoFillBackground(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(d->sidebarView);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);
    setMaximumWidth(SIDEBAR_MAXIMUMWIDTH);
    setFocusProxy(d->sidebarView);
}

void SideBar::initModelData()
{
    auto plugins = PluginManager::instance()->plugins();
    for (auto plugin : plugins) {
        qDebug() << "[PLUGIN]"
                 << "load sidebar item from plugin:" << plugin.first;
        SideBarItem *item = plugin.second->createSideBarItem();
        this->appendItem(item, item->groupName());
    }
}

void SideBar::initConnection()
{
    Q_D(SideBar);
    // do `cd` work
    connect(d->sidebarView, &QListView::activated, this, &SideBar::onItemActivated);
    // context menu
    connect(d->sidebarView, &QListView::customContextMenuRequested, this, &SideBar::onContextMenuRequested);
}

void SideBar::appendItem(SideBarItem *item, const QString &groupName)
{
    Q_D(SideBar);

    item->setGroupName(groupName);
    d->sidebarModel->appendRow(item);
}

int SideBar::findItem(const QUrl &url, bool fuzzy) const
{
    Q_D(const SideBar);

    for (int i = 0; i < d->sidebarModel->rowCount(); ++i) {
        SideBarItem *item = d->sidebarModel->itemFromIndex(i);
        if (item->itemType() == SideBarItem::SidebarItem) {
            if (item->url() == url)
                return i;

            if (!fuzzy)
                continue;
            // TODO: fuzzy
        }
    }

    return -1;
}
