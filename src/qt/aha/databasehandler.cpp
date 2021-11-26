#include "databasehandler.h"
#include "user.h"
#include "employee.h"
#include "supervisor.h"
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QVariantMap>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QSqlQuery>

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent),
      m_username{"JfadHzJmgq"},
      m_password{"mpPExijexc"},
      m_server{"remotemysql.com"},
      m_port{3306}
{}

DatabaseHandler::~DatabaseHandler()
{
    delete obj;
}

bool DatabaseHandler::attemptSignIn(QString username, QString password)
{
    QList<QString> pass = fetch("password","user","username",username);
    if(pass.at(0) == password)
        return true;
    else
        return false;
}

Supervisor DatabaseHandler::getUserInfo(QString username)
{
    QString name, password, eName, eUser, ePass;
    bool isAdmin;

    name = fetch("name","user","username",username).at(0);
    password = fetch("password","user","username",username).at(0);
    if(fetch("is_admin","user","username",username).at(0)=="1")
        isAdmin=true;
    else
        isAdmin=false;

    Supervisor ret = Supervisor(name,Login(username,password),isAdmin);

    // load up with employees
    QList<QString> employees = fetch("emp_username","supervises","Super_unsername",username);
    foreach(QString e,employees)
    {
        eName = fetch("name","user","username",e).at(0);
        eUser = fetch("username","user","username",e).at(0);
        ePass = fetch("password","user","username",e).at(0);
        Employee E = Employee(eName,Login(eUser,ePass));
        ret.addEmployee(E);
    }

    ret.printToDebug();

    return ret;
}

QList<Record> DatabaseHandler::getAllRecords(QList<Employee> employees)
{
    foreach(Employee e, employees)
    {
        QList<QString> data = fetch("website","report","username",e.Username());
        foreach(QString d, data)
        {
            qDebug() << d;
        }
        QList<Record> ret;
        QString website, time, date;
        QSqlQuery wq = QSqlQuery("SELECT website, time, date FROM report WHERE username=\""+e.Username()+"\"",m_db);
        //QSqlQuery tq = QSqlQuery("SELECT time FROM report WHERE username=\""+e.Username()+"\"",m_db);
        //QSqlQuery dq = QSqlQuery("SELECT date FROM report WHERE username=\""+e.Username()+"\"",m_db);
        wq.setForwardOnly(true); //this saves memory and overhead
        while(wq.next())
        {
            website = wq.value(0).toString();
            time = wq.value(1).toString();
            date = wq.value(2).toString();
            qDebug() << website+", "+time+", "+date;
        }

    }
    return QList<Record>();
}

void DatabaseHandler::connectToDB() //application connect with database
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(m_server);
    m_db.setPort(m_port);
    m_db.setDatabaseName(m_username);
    m_db.setUserName(m_username);
    m_db.setPassword(m_password);

    bool opened = m_db.open();

    if(!opened){ qDebug() << "db not opened"; }
}

QList<QString> DatabaseHandler::fetch(QString attr, QString table, QString whereAttr, QString whereVal)
{
    QList<QString> ret;
    QSqlQuery query = QSqlQuery("SELECT "+attr+" FROM "+table+" WHERE "+whereAttr+"=\""+whereVal+"\"",m_db);
    query.setForwardOnly(true); //this saves memory and overhead
    while(query.next())
    {
        ret.append(query.value(0).toString());
    }
    return ret;
}

