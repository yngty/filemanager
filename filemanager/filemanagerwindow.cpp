#include "filemanagerwindow.h"
#include "toolbar.h"
#include "interfaces/sidebar.h"
#include "pluginmanager.h"

#include <DTitlebar>
#include <DToolBar>

#include <QDebug>
#include <QSplitter>
#include <QVBoxLayout>

class FileManagerWindowPrivate
{
public:
    explicit FileManagerWindowPrivate(FileManagerWindow *qq)
        : q_ptr(qq) {}

private:
    QFrame *centralWidget { nullptr };
    SideBar *sideBar { nullptr };
    QFrame *rightView { nullptr };

    QHBoxLayout *midLayout { nullptr };
    QSplitter *splitter { nullptr };

    ToolBar *toolbar { nullptr };
    QFrame *titleFrame { nullptr };
    FileManagerWindow *q_ptr { nullptr };
    Q_DECLARE_PUBLIC(FileManagerWindow)
};

FileManagerWindow::FileManagerWindow(QWidget *parent)
    : DMainWindow(parent),
      d_private(new FileManagerWindowPrivate(this))
{
    PluginManager *manager = PluginManager::instance();
    manager->loadPlugin();
    initUI();
}

FileManagerWindow::~FileManagerWindow()
{
}

void FileManagerWindow::initUI()
{
    Q_D(FileManagerWindow);
    setWindowIcon(QIcon::fromTheme("dde-file-manager"));
    resize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
    setMinimumSize(WINDOW_MINIMUM_WIDTH, WINDOW_MINIMUM_HEIGHT);
    initTitleBar();
    initCentralWidget();
    setCentralWidget(d->centralWidget);
}

void FileManagerWindow::initTitleFrame()
{
    Q_D(FileManagerWindow);
    initToolBar();
    titlebar()->setIcon(QIcon::fromTheme("dde-file-manager", QIcon::fromTheme("system-file-manager")));

    d->titleFrame = new QFrame;

    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setMargin(0);
    titleLayout->setSpacing(0);

    titleLayout->addWidget(d->toolbar);
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(0, 7, 0, 7);
    d->titleFrame->setLayout(titleLayout);
    d->titleFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void FileManagerWindow::initTitleBar()
{
    Q_D(FileManagerWindow);
    initTitleFrame();

    titlebar()->setContentsMargins(0, 0, 0, 0);
    titlebar()->setCustomWidget(d->titleFrame, false);
}

void FileManagerWindow::initToolBar()
{
    Q_D(FileManagerWindow);

    d->toolbar = new ToolBar(this);
    d->toolbar->setObjectName("ToolBar");
}

void FileManagerWindow::initCentralWidget()
{
    Q_D(FileManagerWindow);

    initSplitter();
    d->centralWidget = new QFrame(this);
    d->centralWidget->setObjectName("CentralWidget");

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QWidget *midWidget = new QWidget(this);
    d->midLayout = new QHBoxLayout;
    midWidget->setLayout(d->midLayout);
    d->midLayout->setContentsMargins(0, 0, 0, 0);
    d->midLayout->addWidget(d->splitter);

    mainLayout->addWidget(midWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    d->centralWidget->setLayout(mainLayout);
}

void FileManagerWindow::initSplitter()
{
    Q_D(FileManagerWindow);

    initLeftSideBar();
    initRightView();

    d->splitter = new QSplitter(Qt::Horizontal, this);
    d->splitter->addWidget(d->sideBar);
    d->splitter->addWidget(d->rightView);
    d->splitter->setChildrenCollapsible(false);
}

void FileManagerWindow::initLeftSideBar()
{
    Q_D(FileManagerWindow);

    d->sideBar = new SideBar(this);
    d->sideBar->setContentsMargins(0, 0, 0, 0);

    d->sideBar->setObjectName("SideBar");
    d->sideBar->setMaximumWidth(SideBar::SIDEBAR_MAXIMUMWIDTH);
    d->sideBar->setMinimumWidth(SideBar::SIDEBAR_MINIMUMWIDTH);
}

void FileManagerWindow::initRightView()
{
    Q_D(FileManagerWindow);
    d->rightView = new QFrame;
    QSizePolicy sp = d->rightView->sizePolicy();

    sp.setHorizontalStretch(1);
    d->rightView->setSizePolicy(sp);
}
