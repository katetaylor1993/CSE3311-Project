#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtSql/QSqlDatabase>

class DatabaseHandler : public QObject
{
    Q_OBJECT
private:
    static DatabaseHandler * obj;
    explicit DatabaseHandler(QObject *parent = nullptr);
public:
    static DatabaseHandler* getInstance()
    {
        if(obj == nullptr)
        {
            static DatabaseHandler instance;
            obj = &instance;
        }
        return obj;
    }
    ~DatabaseHandler();

    // Database Authorization
    void setAPIKey( const QString & apiKey);
    void signUserUp( const QString & emailAddress, const QString & password);
    void connectToDB();
    QString readUsersName(QString username);


public slots:
    void networkReplyReadyRead();
    void performAuthenticatedDatabaseCall();

signals:
    void userSignedIn();
    void criticalError();
private:
    QString m_username;
    QString m_password;
    QString m_server;
    int m_port;
    QSqlDatabase m_db;

    QNetworkAccessManager * m_networkManager;
    QNetworkReply * m_networkReply;

    // Database Authorization
    QString m_apiKey;
    QString m_idToken;
    void performPOST( const QString & url, const QJsonDocument & payload );
    void parseResponse( const QByteArray & response);


};

#endif // DATABASEHANDLER_H
