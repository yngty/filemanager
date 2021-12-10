#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QFrame>

class ToolBarPrivate;
class ToolBar : public QFrame
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar();

private:
    void initUI();
    void initAddressToolBar();
    void initContollerToolBar();

    enum {
        ButtonWidth = 36,
        ButtonHeigt = 36,
        IconWidth = 16,
        IconHeight = 16
    };

    QScopedPointer<ToolBarPrivate> d_private;
    Q_DECLARE_PRIVATE_D(d_private, ToolBar)
};

#endif   // TOOLBAR_H
