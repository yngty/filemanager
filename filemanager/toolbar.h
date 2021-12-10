#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QFrame>

class ToolBar : public QFrame
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = nullptr);

private:
    void initUI();
};

#endif   // TOOLBAR_H
