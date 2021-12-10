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

SideBar::SideBar(QWidget *parent)
    : QWidget(parent),
      sidebarView(new SideBarView(this)),
      sidebarModel(new SideBarModel(this))
{
    initUI();
    initModelData();
    initConnection();
}

QWidget *SideBar::view()
{
    return sidebarView;
}

void SideBar::onItemActivated(const QModelIndex &index)
{
    SideBarItem *item = sidebarModel->itemFromIndex(index);

    QString identifierStr = item->registeredHandler();

    QScopedPointer<SideBarItemInterface> interface(SideBarManager::instance()->createByIdentifier(identifierStr));
    if (interface) {
        interface->cdAction();
    }
}

void SideBar::onContextMenuRequested(const QPoint &pos)
{
    QModelIndex modelIndex = sidebarView->indexAt(pos);
    if (!modelIndex.isValid()) {
        return;
    }

    SideBarItem *item = sidebarModel->itemFromIndex(modelIndex);

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
    sidebarView->setModel(sidebarModel);
    sidebarView->setItemDelegate(new SideBarItemDelegate(sidebarView));
    sidebarView->setViewportMargins(10, 0, sidebarView->verticalScrollBar()->sizeHint().width(), 0);
    sidebarView->setContextMenuPolicy(Qt::CustomContextMenu);
    sidebarView->setFrameShape(QFrame::Shape::NoFrame);
    sidebarView->setAutoFillBackground(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(sidebarView);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);
    setMaximumWidth(SIDEBAR_MAXIMUMWIDTH);
    setFocusProxy(sidebarView);
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
    // do `cd` work
    connect(sidebarView, &QListView::activated, this, &SideBar::onItemActivated);
    // context menu
    connect(sidebarView, &QListView::customContextMenuRequested, this, &SideBar::onContextMenuRequested);
}

void SideBar::appendItem(SideBarItem *item, const QString &groupName)
{
    item->setGroupName(groupName);
    sidebarModel->appendRow(item);
}
