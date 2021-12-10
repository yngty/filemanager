#ifndef SIDEBARITEMDELEGATE_H
#define SIDEBARITEMDELEGATE_H

#include <DStyledItemDelegate>

DWIDGET_USE_NAMESPACE

class SideBarItemDelegate : public DStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SideBarItemDelegate(QAbstractItemView *parent = nullptr);

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    void paintSeparator(QPainter *painter, const QStyleOptionViewItem &option) const;
};

#endif   // SIDEBARITEMDELEGATE_H
