#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QUrl>
DWIDGET_USE_NAMESPACE

class BaseView;
class FileManagerWindowPrivate;
class FileManagerWindow : public DMainWindow
{
    Q_OBJECT
public:
    FileManagerWindow(QWidget *parent = nullptr);
    virtual ~FileManagerWindow() override;

signals:
    void currentUrlChanged();
    void currentViewStateChanged();
    void selectUrlChanged(const QList<QUrl> &urlList);

public slots:
    bool cd(const QUrl &url);
    bool cdForTabByView(BaseView *view, const QUrl &url);

private:
    void initUI();
    void initTitleFrame();
    void initTitleBar();

    void initToolBar();
    void initCentralWidget();
    void initSplitter();
    void initLeftSideBar();
    void initRightView();
    void initViewLayout();

    QScopedPointer<FileManagerWindowPrivate> d_private;
    Q_DECLARE_PRIVATE_D(d_private, FileManagerWindow)

    Q_DISABLE_COPY(FileManagerWindow)
};

#endif   // MAINWINDOW_H
