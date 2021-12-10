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
    QFrame *m_addressToolBar { nullptr };
    DButtonBoxButton *m_backButton { nullptr };
    DButtonBoxButton *m_forwardButton { nullptr };
    QFrame *crumbAndSearch { nullptr };
    CrumbBar *m_crumbWidget { nullptr };
    QPushButton *m_searchButton { nullptr };
    QToolButton *m_detailButton { nullptr };
    ToolBar *q_ptr;
    Q_DECLARE_PUBLIC(ToolBar)
};

ToolBar::ToolBar(QWidget *parent)
    : QFrame(parent), d_private(new ToolBarPrivate(this))

{
    initUI();
}

ToolBar::~ToolBar()
{
}

void ToolBar::initUI()
{
    Q_D(ToolBar);

    setFocusPolicy(Qt::NoFocus);
    initAddressToolBar();
    initContollerToolBar();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(d->m_addressToolBar);

    mainLayout->addSpacing(0);
    mainLayout->setContentsMargins(14, 0, 4, 0);
    setLayout(mainLayout);
}

void ToolBar::initAddressToolBar()
{
    Q_D(ToolBar);
    d->m_addressToolBar = new QFrame;
    d->m_addressToolBar->setObjectName("AddressToolBar");

    QHBoxLayout *backForwardLayout = new QHBoxLayout;

    d->m_backButton = new DButtonBoxButton(QStyle::SP_ArrowBack);

    d->m_backButton->setDisabled(true);
    d->m_backButton->setFixedWidth(ButtonWidth);

    d->m_forwardButton = new DButtonBoxButton(QStyle::SP_ArrowForward);
    d->m_forwardButton->setDisabled(true);
    d->m_forwardButton->setFixedWidth(ButtonWidth);

    QList<DButtonBoxButton *> buttonList;
    buttonList << d->m_backButton << d->m_forwardButton;

    DButtonBox *buttonBox = new DButtonBox(this);

    buttonBox->setButtonList(buttonList, false);
    buttonBox->setFocusPolicy(Qt::NoFocus);
    backForwardLayout->addWidget(buttonBox);
    backForwardLayout->setSpacing(0);
    backForwardLayout->setContentsMargins(0, 0, 0, 0);

    d->crumbAndSearch = new QFrame;
    d->crumbAndSearch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    d->m_crumbWidget = new CrumbBar(this);

    d->m_searchButton = new QPushButton(this);
    d->m_searchButton->setObjectName("searchButton");
    d->m_searchButton->setFixedSize(ButtonWidth, ButtonHeigt);
    d->m_searchButton->setFocusPolicy(Qt::NoFocus);
    d->m_searchButton->setFlat(true);
    d->m_searchButton->setIcon(QIcon::fromTheme("search"));
    d->m_searchButton->setIconSize(QSize(IconWidth, IconHeight));

    QHBoxLayout *comboLayout = new QHBoxLayout;
    comboLayout->addWidget(d->m_crumbWidget);
    comboLayout->addWidget(d->m_searchButton);
    comboLayout->setContentsMargins(0, 0, 0, 0);

    d->crumbAndSearch->setLayout(comboLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(backForwardLayout);
    mainLayout->addWidget(d->crumbAndSearch);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    d->m_addressToolBar->setLayout(mainLayout);
}

void ToolBar::initContollerToolBar()
{
}
