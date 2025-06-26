#ifndef FORMDATAREQUESTSENDER_H
#define FORMDATAREQUESTSENDER_H

#include <QObject>

class FormDataRequestSender : public QObject
{
    Q_OBJECT
public:
    explicit FormDataRequestSender(QObject *parent = nullptr);
    FormDataRequestSender()=default;

    //绑定特定的回调函数，针对不同的响应做回调处理
    using SuccessCallback = std::function<void(const QByteArray &)>;
    using FailureCallback = std::function<void(const QString &)>;

    //封装post请求，
    void sendPostRequest(const QUrl &url, const JsonRequest &request,SuccessCallback onSuccess,FailureCallback onFail);

    void sendPostRequest(
        const QUrl &url,
        const QString &fileFieldName,
        const QStringList &filePaths,
        const QMap<QString, QVariant> &formFields,
        std::function<void(const QByteArray&)> onSuccess,
        std::function<void(const QString&)> onFail
        );

public:


private:

signals:

};

#endif // FORMDATAREQUESTSENDER_H
