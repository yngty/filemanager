#include "commoncrumbcontroller.h"
#include <QDebug>

CommonCrumbController::CommonCrumbController(QObject *parent)
    : CrumbInterface(parent)
{
}

CommonCrumbController::~CommonCrumbController()
{
}

bool CommonCrumbController::supportedUrl(QUrl url)
{
    return ((url.scheme() == "plugin") && (url.host() == "phone"));
}

QList<CrumbData> CommonCrumbController::seprateUrl(const QUrl &url)
{
    Q_UNUSED(url);

    QList<CrumbData> list;

    QString text = tr("My Phone");
    QString iconName = "phone-android";
    list.append(CrumbData(fromFile("/"), text, iconName));

    QStringList urllist;
    urllist.clear();

    QString path = url.path();
    if (!path.isEmpty()) {
        if (path.contains("/")) {
            QStringList listvalue = path.split("/");
            //qWarning() << "listvalue size" << listvalue.size();
            for (int i = 0; i < listvalue.size(); i++) {
                QString value = listvalue.at(i);
                //qWarning() << "valuevaluevalue" << value;
                if (!value.isEmpty()) {
                    urllist.append(value);
                }
            }
        }
    }

    for (int i = 0; i < urllist.size(); i++) {
        QString strurl = "";
        for (int j = 0; j <= i; j++) {
            strurl = strurl + QString("/") + urllist.at(j);
        }

        list.append(CrumbData(fromFile(strurl), urllist.at(i), ""));
    }

    for (int i = 0; i < list.size(); i++) {
        qWarning() << "list url" << list.at(i).url;
    }

    return list;
}

QUrl CommonCrumbController::fromFile(const QString &filePath)
{
    QUrl url;
    url.setScheme("common");
    url.setHost("phone");
    url.setPath(filePath);

    return url;
}

void CommonCrumbController::processAction(ActionType type)
{
}

void CommonCrumbController::crumbUrlChangedBehavior(const QUrl url)
{
}

void CommonCrumbController::requestCompletionList(const QUrl &url)
{
}

void CommonCrumbController::cancelCompletionListTransmission()
{
}
