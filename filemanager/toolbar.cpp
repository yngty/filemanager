#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent)
    : QFrame(parent)
{
    initUI();
}

void ToolBar::initUI()
{
    setFocusPolicy(Qt::NoFocus);
}
