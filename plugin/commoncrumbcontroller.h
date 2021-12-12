#ifndef COMMONCRUMBCONTROLLER_H
#define COMMONCRUMBCONTROLLER_H

#include "interfaces/crumbinterface.h"

class CommonCrumbController : public CrumbInterface
{
public:
    explicit CommonCrumbController(QObject *parent = nullptr);

    ~CommonCrumbController() = default;
    virtual bool supportedUrl(QUrl url) override;

    virtual QList<CrumbData> seprateUrl(const QUrl &url) override;

    virtual void processAction(ActionType type) override;
    virtual void crumbUrlChangedBehavior(const QUrl url) override;
    virtual void requestCompletionList(const QUrl &url) override;
    virtual void cancelCompletionListTransmission() override;

    QUrl fromFile(const QString &filePath);
};

#endif   // COMMONCRUMBCONTROLLER_H
