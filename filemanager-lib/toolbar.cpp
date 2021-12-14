#include "toolbar.h"
#include "crumbbar.h"

#include <DButtonBox>

#include <QToolButton>
#include <QPushButton>
#include <QHBoxLayout>

DWIDGET_USE_NAMESPACE

class ToolBarPrivate
{
public:
    explicit ToolBarPrivate(ToolBar *qq)
        : q_ptr(qq) {}

private:
    QFrame *addressToolBar { nullptr };
    DButtonBoxButton *backButton { nullptr };
    DButtonBoxButton *forwardButton { nullptr };
    QFrame *crumbAndSearch { nullptr };
    CrumbBar *crumbWidget { nullptr };
    QPushButton *searchButton { nullptr };
    QToolButton *detailButton { nullptr };
    ToolBar *q_ptr;
    Q_DECLARE_PUBLIC(ToolBar)
};

ToolBar::ToolBar(QWidget *parent)
    : QFrame(parent), d_private(new ToolBarPrivate(this))

{
    initUI();
    initConnect();
}

ToolBar::~ToolBar()
{
}

void ToolBar::currentUrlChanged(const QUrl &url)
{
    emit toolbarUrlChanged(url);
}

void ToolBar::initUI()
{
    Q_D(ToolBar);

    setFocusPolicy(Qt::NoFocus);
    initAddressToolBar();
    initContollerToolBar();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(d->addressToolBar);

    mainLayout->addSpacing(0);
    mainLayout->setContentsMargins(14, 0, 4, 0);
    setLayout(mainLayout);
}

void ToolBar::initAddressToolBar()
{
    Q_D(ToolBar);
    d->addressToolBar = new QFrame;
    d->addressToolBar->setObjectName("AddressToolBar");

    QHBoxLayout *backForwardLayout = new QHBoxLayout;

    d->backButton = new DButtonBoxButton(QStyle::SP_ArrowBack);

    d->backButton->setDisabled(true);
    d->backButton->setFixedWidth(ButtonWidth);

    d->forwardButton = new DButtonBoxButton(QStyle::SP_ArrowForward);
    d->forwardButton->setDisabled(true);
    d->forwardButton->setFixedWidth(ButtonWidth);

    QList<DButtonBoxButton *> buttonList;
    buttonList << d->backButton << d->forwardButton;

    DButtonBox *buttonBox = new DButtonBox(this);

    buttonBox->setButtonList(buttonList, false);
    buttonBox->setFocusPolicy(Qt::NoFocus);
    backForwardLayout->addWidget(buttonBox);
    backForwardLayout->setSpacing(0);
    backForwardLayout->setContentsMargins(0, 0, 0, 0);

    d->crumbAndSearch = new QFrame;
    d->crumbAndSearch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    d->crumbWidget = new CrumbBar(this);

    d->searchButton = new QPushButton(this);
    d->searchButton->setObjectName("searchButton");
    d->searchButton->setFixedSize(ButtonWidth, ButtonHeigt);
    d->searchButton->setFocusPolicy(Qt::NoFocus);
    d->searchButton->setFlat(true);
    d->searchButton->setIcon(QIcon::fromTheme("search"));
    d->searchButton->setIconSize(QSize(IconWidth, IconHeight));

    QHBoxLayout *comboLayout = new QHBoxLayout;
    comboLayout->addWidget(d->crumbWidget);
    comboLayout->addWidget(d->searchButton);
    comboLayout->setContentsMargins(0, 0, 0, 0);

    d->crumbAndSearch->setLayout(comboLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(backForwardLayout);
    mainLayout->addWidget(d->crumbAndSearch);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    d->addressToolBar->setLayout(mainLayout);
}

void ToolBar::initContollerToolBar()
{
}

void ToolBar::initConnect()
{
    Q_D(ToolBar);
    connect(this, &ToolBar::toolbarUrlChanged, d->crumbWidget, &CrumbBar::updateCurrentUrl);
}
