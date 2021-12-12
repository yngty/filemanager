#ifndef CRUMBINTERFACE_H
#define CRUMBINTERFACE_H

#include <QObject>
#include <QUrl>

class CrumbData
{
public:
    CrumbData(QUrl url = QUrl(), QString displayText = QString(), QString iconName = QString(), QString iconKey = "icon");

    operator QString() const;

    QUrl url = QUrl();
    QString iconName = QString();   // icon group name
    QString displayText = QString();
    QString iconKey = "icon";   // icon key
};

class CrumbBar;
class CrumbInterfacePrivate;
class CrumbInterface : public QObject
{
    Q_OBJECT
public:
    explicit CrumbInterface(QObject *parent = nullptr);
    virtual ~CrumbInterface();

    // Actions may cause AddressBar focusOut
    enum ActionType {
        EscKeyPressed,
        ClearButtonPressed,
        AddressBarLostFocus,
        PauseButtonClicked
    };

    virtual void processAction(ActionType type) = 0;
    virtual void crumbUrlChangedBehavior(const QUrl url) = 0;
    virtual CrumbBar *crumbBar() final;
    virtual void setCrumbBar(CrumbBar *crumbBar) final;
    virtual bool supportedUrl(QUrl) = 0;
    virtual QList<CrumbData> seprateUrl(const QUrl &url) = 0;
    virtual void requestCompletionList(const QUrl &url) = 0;
    virtual void cancelCompletionListTransmission() = 0;
signals:
    void completionFound(const QStringList &completions);   //< emit multiple times with less or equials to 10 items in a group.
    void completionListTransmissionCompleted();   //< emit when all avaliable completions has been sent.

private:
    QScopedPointer<CrumbInterfacePrivate> d_ptr;
    Q_DECLARE_PRIVATE(CrumbInterface)
};
#endif   // CRUMBINTERFACE_H
