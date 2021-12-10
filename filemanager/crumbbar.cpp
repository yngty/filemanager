#include "crumbbar.h"

class CrumbBarPrivate
{
public:
    explicit CrumbBarPrivate(CrumbBar *qq)
        : q_ptr(qq)
    {
    }
    CrumbBar *q_ptr { nullptr };
};

CrumbBar::CrumbBar(QWidget *parent)
    : QFrame(parent), d_private(new CrumbBarPrivate(this))
{
    setFrameShape(QFrame::NoFrame);
}

CrumbBar::~CrumbBar()
{
}
