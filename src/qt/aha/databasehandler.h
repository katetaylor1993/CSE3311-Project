#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    ~DatabaseHandler();

    // Database Authorization
    void setAPIKey( const QString & apiKey);
    void signUserUp( const QString & emailAddress, const QString & password);
    void signUserIn( const QString & emailAddress, const QString & password);

public slots:
    void networkReplyReadyRead();
    void performAuthenticatedDatabaseCall();

signals:
    void userSignedIn();
private:
    QNetworkAccessManager * m_networkManager;
    QNetworkReply * m_networkReply;

    // Database Authorization
    QString m_apiKey;
    QString m_idToken;
    void performPOST( const QString & url, const QJsonDocument & payload );
    void parseResponse( const QByteArray & response);


};

#endif // DATABASEHANDLER_H
