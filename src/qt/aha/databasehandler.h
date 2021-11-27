#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtSql/QSqlDatabase>
#include <QFile>

#include "record.h"
#include "supervisor.h"

struct websiteCategory_t { QString wesbite; QString category; };
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
    User * getUserInfo(QString username);
    QString attemptSignIn(QString username, QString password);
    QList<Record> getAllRecords(QList<Employee> employees);
    void updateCategory(QString url, QString cat);
    QString getCategory(QString website);


public slots:

signals:
    void criticalError();
    void recordsAreReady(QList<Record> records);
    void loggedIn(QString username);
    void badLoginInfo();
private:
    QString m_username;
    QString m_password;
    QString m_server;
    int m_port;
    QSqlDatabase m_db;
    QFile * m_categories;
    QMap<QString, QString> m_catMap;

    void fillCategories();

    QList<QString> fetch(QString attr, QString table, QString whereAttr, QString whereVal);
};

#endif // DATABASEHANDLER_H
