#include "databasehandler.h"
#include "user.h"
#include "employee.h"

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
    QList<QString> pass = getOneAttribute("password","user","username",username);
    if(pass.at(0) == password)
        return true;
    else
        return false;
}

Supervisor DatabaseHandler::getUserInfo(QString username)
{
    QString name, password, eName, eUser, ePass;
    bool isAdmin;

    name = getOneAttribute("name","user","username",username).at(0);
    password = getOneAttribute("password","user","username",username).at(0);
    if(getOneAttribute("is_admin","user","username",username).at(0)=="1")
        isAdmin=true;
    else
        isAdmin=false;

    Supervisor ret = Supervisor(name,Login(username,password),isAdmin);

    // load up with employees
    QList<QString> employees = getOneAttribute("emp_username","supervises","Super_unsername",username);
    foreach(QString e,employees)
    {
        eName = getOneAttribute("name","user","username",e).at(0);
        eUser = getOneAttribute("username","user","username",e).at(0);
        ePass = getOneAttribute("password","user","username",e).at(0);
        Employee E = Employee(eName,Login(eUser,ePass));
        ret.addEmployee(E);
    }

    ret.printToDebug();

    return ret;
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

QList<QString> DatabaseHandler::getOneAttribute(QString attr, QString table, QString whereAttr, QString whereVal)
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

