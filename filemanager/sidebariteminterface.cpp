#include "interfaces/sidebariteminterface.h"
#include "interfaces/sidebaritem.h"
#include "interfaces/sidebar.h"
//#include "filemanagerwindow.h"

SideBarItemInterface::SideBarItemInterface(QObject *parent)
    : QObject(parent)
{
}

SideBarItemInterface::~SideBarItemInterface()
{
}

void SideBarItemInterface::cdAction(const SideBar *sidebar, const SideBarItem *item)
{
    //    FileManagerWindow *wnd = qobject_cast<FileManagerWindow *>(sidebar->topLevelWidget());
    //    if (item->itemType() != SideBarItem::Separator) {
    //        qDebug() << " item->url() " << item->url();

    //        wnd->cd(item->url());   // don't `setChecked` here, wait for a signal.
    //    }
}
