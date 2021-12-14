#include "sidebaritemdelegate.h"
#include "interfaces/sidebaritem.h"
#include <QPainter>
#include <qdrawutil.h>

SideBarItemDelegate::SideBarItemDelegate(QAbstractItemView *parent)
    : DStyledItemDelegate(parent)
{
}

void SideBarItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant v = index.data(SideBarItem::ItemTypeRole);
    if (v.isValid() && v.toInt() == SideBarItem::Separator) {
        return paintSeparator(painter, option);
    }
    return DStyledItemDelegate::paint(painter, option, index);
}

QSize SideBarItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return DStyledItemDelegate::sizeHint(option, index);
}

void SideBarItemDelegate::paintSeparator(QPainter *painter, const QStyleOptionViewItem &option) const
{
    painter->save();

    int yPoint = option.rect.top() + option.rect.height() / 2;
    qDrawShadeLine(painter, 0, yPoint, option.rect.width(), yPoint, option.palette);

    painter->restore();
}
