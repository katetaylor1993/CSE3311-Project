#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtSql/QSqlDatabase>

#include "record.h"
#include "supervisor.h"

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

    void connectToDB();
    Supervisor getUserInfo(QString username);
    bool attemptSignIn(QString username, QString password);


public slots:

signals:
    void criticalError();
    void recordsAreReady(QList<Record> records);
private:
    QString m_username;
    QString m_password;
    QString m_server;
    int m_port;
    QSqlDatabase m_db;

    QList<QString> getOneAttribute(QString attr, QString table, QString whereAttr, QString whereVal);
};

#endif // DATABASEHANDLER_H
