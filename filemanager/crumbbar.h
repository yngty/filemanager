#ifndef CRUMBBAR_H
#define CRUMBBAR_H

#include <QFrame>

class CrumbBarPrivate;
class CrumbBar : public QFrame
{
public:
    explicit CrumbBar(QWidget *parent = nullptr);
    ~CrumbBar();

    void updateCrumbs(const QUrl &url);
public Q_SLOTS:
    void updateCurrentUrl(const QUrl &url);

private:
    QScopedPointer<CrumbBarPrivate> d_private;
    Q_DECLARE_PRIVATE(CrumbBar)
};

#endif   // CRUMBBAR_H
