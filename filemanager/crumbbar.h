#ifndef CRUMBBAR_H
#define CRUMBBAR_H

#include <QFrame>

class CrumbBarPrivate;
class CrumbBar : public QFrame
{
public:
    explicit CrumbBar(QWidget *parent = nullptr);
    ~CrumbBar();

private:
    QScopedPointer<CrumbBarPrivate> d_private;
    Q_DECLARE_PRIVATE(CrumbBar)
};

#endif   // CRUMBBAR_H
