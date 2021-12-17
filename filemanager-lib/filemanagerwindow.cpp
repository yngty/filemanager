#include "filemanagerwindow.h"
#include "interfaces/baseview.h"
#include "interfaces/sidebar.h"
#include "toolbar.h"
#include "pluginmanager.h"
#include "viewmanager.h"

#include <DTitlebar>
#include <DToolBar>

#include <QDebug>
#include <QSplitter>
#include <QVBoxLayout>
#include <QStackedLayout>

class FileManagerWindowPrivate
{
public:
    explicit FileManagerWindowPrivate(FileManagerWindow *qq)
        : q_ptr(qq) {}

private:
    enum WindowEdge {
        WINDOW_DEFAULT_WIDTH = 960,
        WINDOW_DEFAULT_HEIGHT = 540,
        WINDOW_MINIMUM_WIDTH = 760,
        WINDOW_MINIMUM_HEIGHT = 420
    };

    QFrame *centralWidget { nullptr };
    SideBar *sideBar { nullptr };
    QFrame *rightView { nullptr };
    QHBoxLayout *midLayout { nullptr };
    QSplitter *splitter { nullptr };
    ToolBar *toolbar { nullptr };
    QFrame *titleFrame { nullptr };

    QVBoxLayout *rightViewLayout { nullptr };
    QStackedLayout *viewStackLayout { nullptr };

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

bool FileManagerWindow::cd(const QUrl &url)
{
    Q_D(FileManagerWindow);
    d->toolbar->currentUrlChanged(url);
    BaseView *view = ViewManager::instance()->createViewByUrl(url);
    if (view) {
        d->viewStackLayout->addWidget(view->widget());
        d->viewStackLayout->setCurrentWidget(view->widget());
    }
    return true;
}

bool FileManagerWindow::cdForTabByView(BaseView *view, const QUrl &url)
{
    return true;
}

void FileManagerWindow::initUI()
{
    Q_D(FileManagerWindow);
    setWindowIcon(QIcon::fromTheme("dde-file-manager"));
    resize(FileManagerWindowPrivate::WINDOW_DEFAULT_WIDTH, FileManagerWindowPrivate::WINDOW_DEFAULT_HEIGHT);
    setMinimumSize(FileManagerWindowPrivate::WINDOW_MINIMUM_WIDTH, FileManagerWindowPrivate::WINDOW_MINIMUM_HEIGHT);
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

    connect(this, &FileManagerWindow::currentUrlChanged, this, [this, d] {
        d->sideBar->setCurrentUrl(QUrl());
    });
}

void FileManagerWindow::initRightView()
{
    Q_D(FileManagerWindow);

    initViewLayout();
    d->rightView = new QFrame;
    QSizePolicy sp = d->rightView->sizePolicy();

    sp.setHorizontalStretch(1);
    d->rightView->setSizePolicy(sp);
    d->rightViewLayout = new QVBoxLayout;
    d->rightViewLayout->addLayout(d->viewStackLayout, 1);
    d->rightViewLayout->setSpacing(0);
    d->rightViewLayout->setContentsMargins(0, 0, 0, 0);
    d->rightView->setLayout(d->rightViewLayout);
}

void FileManagerWindow::initViewLayout()
{
    Q_D(FileManagerWindow);

    d->viewStackLayout = new QStackedLayout;
    d->viewStackLayout->setSpacing(0);
    d->viewStackLayout->setContentsMargins(0, 0, 0, 0);
}
