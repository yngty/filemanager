#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>

DWIDGET_USE_NAMESPACE

class FileManagerWindowPrivate;
class FileManagerWindow : public DMainWindow
{
    Q_OBJECT

public:
    FileManagerWindow(QWidget *parent = nullptr);
    ~FileManagerWindow() override;

private:
    enum WindowEdge {
        WINDOW_DEFAULT_WIDTH = 960,
        WINDOW_DEFAULT_HEIGHT = 540,
        WINDOW_MINIMUM_WIDTH = 760,
        WINDOW_MINIMUM_HEIGHT = 420
    };

    void initUI();
    void initTitleFrame();
    void initTitleBar();

    void initToolBar();
    void initCentralWidget();
    void initSplitter();
    void initLeftSideBar();
    void initRightView();

    QScopedPointer<FileManagerWindowPrivate> d_private;
    Q_DECLARE_PRIVATE_D(d_private, FileManagerWindow)

    Q_DISABLE_COPY(FileManagerWindow)
};

#endif   // MAINWINDOW_H
