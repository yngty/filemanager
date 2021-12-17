#include "interfaces/crumbinterface.h"
#include "crumbbar.h"

CrumbData::CrumbData(QUrl url, QString displayText, QString iconName, QString iconKey)
    : url(url), iconName(iconName), displayText(displayText), iconKey(iconKey)
{
}

class CrumbInterfacePrivate
{

public:
    explicit CrumbInterfacePrivate(CrumbInterface *qq);

    CrumbBar *crumbBar { nullptr };

    CrumbInterface *q_ptr { nullptr };

    Q_DECLARE_PUBLIC(CrumbInterface)
};

CrumbInterfacePrivate::CrumbInterfacePrivate(CrumbInterface *qq)
    : q_ptr(qq)
{
}

CrumbInterface::CrumbInterface(QObject *parent)
    : QObject(parent),
      d_ptr(new CrumbInterfacePrivate(this))
{
}

CrumbInterface::~CrumbInterface()
{
}

void CrumbInterface::crumbUrlChangedBehavior(const QUrl url)
{
    crumbBar()->updateCrumbs(url);
}

CrumbBar *CrumbInterface::crumbBar()
{
    Q_D(CrumbInterface);
    return d->crumbBar;
}

void CrumbInterface::setCrumbBar(CrumbBar *crumbBar)
{
    Q_D(CrumbInterface);
    d->crumbBar = crumbBar;
}
