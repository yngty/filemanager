#include "crumbbar.h"
#include "crumblistviewmodel.h"
#include "interfaces/crumbinterface.h"
#include "crumbmanager.h"

#include <DListView>

#include <QPushButton>
#include <QHBoxLayout>

DWIDGET_USE_NAMESPACE

class CrumbBarPrivate
{
public:
    explicit CrumbBarPrivate(CrumbBar *qq);

private:
    void initUI();
    void clearCrumbs();
    void updateController(const QUrl &url);

private:
    enum {
        ButtonWidth = 24,
        ButtonHeight = 24,
        IconWidth = 16,
        IconHeight = 16
    };
    QPushButton leftArrow;
    QPushButton rightArrow;
    DListView crumbListView;
    CrumbListviewModel *crumbListviewModel { nullptr };

    CrumbInterface *crumbController { nullptr };

    CrumbBar *q_ptr { nullptr };
    Q_DECLARE_PUBLIC(CrumbBar)
};

CrumbBarPrivate::CrumbBarPrivate(CrumbBar *qq)
    : q_ptr(qq)
{
    initUI();
}
void CrumbBarPrivate::initUI()
{
    Q_Q(CrumbBar);

    // Arrows
    QSize size(ButtonWidth, ButtonHeight), iconSize(IconWidth, IconHeight);

    leftArrow.setFocusPolicy(Qt::NoFocus);
    leftArrow.setIcon(QIcon::fromTheme("go-previous"));
    rightArrow.setIcon(QIcon::fromTheme("go-next"));
    rightArrow.setFocusPolicy(Qt::NoFocus);

    leftArrow.setFixedSize(size);
    leftArrow.setIconSize(iconSize);
    rightArrow.setFixedSize(size);
    rightArrow.setIconSize(iconSize);
    leftArrow.setFlat(true);
    rightArrow.setFlat(true);
    leftArrow.hide();
    rightArrow.hide();

    // Crumb List Layout
    crumbListView.setObjectName("DCrumbListScrollArea");

    crumbListView.setItemSpacing(10);
    crumbListView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    crumbListView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    crumbListView.setFocusPolicy(Qt::NoFocus);

    crumbListView.setContentsMargins(0, 0, 0, 0);
    crumbListView.setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    crumbListView.setIconSize({ 16, 16 });
    crumbListView.setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
    crumbListView.setOrientation(QListView::LeftToRight, false);
    crumbListView.setEditTriggers(QAbstractItemView::NoEditTriggers);
    crumbListView.setDragDropMode(QAbstractItemView::DragDropMode::NoDragDrop);

    crumbListviewModel = new CrumbListviewModel(q);
    crumbListView.setModel(crumbListviewModel);
    crumbListView.setContextMenuPolicy(Qt::CustomContextMenu);

    // for first icon item icon AlignCenter...
    class IconItemDelegate : public DStyledItemDelegate
    {
    public:
        explicit IconItemDelegate(QAbstractItemView *parent = nullptr)
            : DStyledItemDelegate(parent)
        {
            setItemSpacing(10);
        }

        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
        {
            QStyleOptionViewItem opt = option;
            opt.decorationAlignment = Qt::AlignCenter;
            DStyledItemDelegate::paint(painter, opt, index);
        }
    };
    crumbListView.setItemDelegateForRow(0, new IconItemDelegate(&crumbListView));

    // Crumb Bar Layout
    QHBoxLayout *crumbBarLayout = new QHBoxLayout(q);
    crumbBarLayout->addWidget(&leftArrow);
    crumbBarLayout->addWidget(&crumbListView);
    crumbBarLayout->addWidget(&rightArrow);
    crumbBarLayout->setContentsMargins(0, 0, 0, 0);
    crumbBarLayout->setSpacing(0);
    q->setLayout(crumbBarLayout);
}

void CrumbBarPrivate::clearCrumbs()
{
    leftArrow.hide();
    rightArrow.hide();

    if (crumbListviewModel)
        crumbListviewModel->removeAll();
}

void CrumbBarPrivate::updateController(const QUrl &url)
{
    Q_Q(CrumbBar);

    if (!crumbController || !crumbController->supportedUrl(url)) {
        if (crumbController) {
            crumbController->deleteLater();
        }
        crumbController = CrumbManager::instance()->createControllerByUrl(url, q);
        if (!crumbController) {
            qDebug() << "Unsupported url / scheme: " << url;
        } else
            crumbController->setParent(q_ptr);
    }
}

CrumbBar::CrumbBar(QWidget *parent)
    : QFrame(parent),
      d_private(new CrumbBarPrivate(this))
{
    setFrameShape(QFrame::NoFrame);
}

CrumbBar::~CrumbBar()
{
}

void CrumbBar::updateCrumbs(const QUrl &url)
{
    Q_D(CrumbBar);

    d->clearCrumbs();

    if (!d->crumbController) {
        qWarning("No controller found when trying to call CrumbBar::updateCrumbs() !!!");
        qDebug() << "updateCrumbs (no controller) : " << url;
        return;
    }

    QList<CrumbData> crumbDataList = d->crumbController->seprateUrl(url);

    for (const CrumbData &c : crumbDataList) {
        if (d->crumbListviewModel) {
            QString iconName = c.iconName;
            QStandardItem *listitem = nullptr;
            if (!iconName.isEmpty()) {
                listitem = new QStandardItem(QIcon::fromTheme(iconName), QString());
            } else {
                listitem = new QStandardItem(c.displayText);
            }
            listitem->setTextAlignment(Qt::AlignCenter);   //垂直与水平居中
            listitem->setCheckable(false);
            listitem->setData(c.url, CrumbListviewModel::FileUrlRole);
            d->crumbListviewModel->appendRow(listitem);
        }
    }

    if (d->crumbListView.selectionModel() && d->crumbListviewModel)
        d->crumbListView.selectionModel()->select(d->crumbListviewModel->lastIndex(), QItemSelectionModel::Select);
}

void CrumbBar::updateCurrentUrl(const QUrl &url)
{
    Q_D(CrumbBar);

    d->updateController(url);
}
