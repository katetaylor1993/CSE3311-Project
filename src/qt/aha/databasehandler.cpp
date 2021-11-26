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
#include <QSqlError>
#include <QDate>

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
    if(pass.isEmpty()) {return false;}
    if(pass.at(0) == password)
        getUserInfo(username);
    else
        emit badLoginInfo();
    return true;
}

void DatabaseHandler::getUserInfo(QString username)
{
    QString name, password, eName, eUser, ePass;

    name = fetch("name","user","username",username).at(0);
    password = fetch("password","user","username",username).at(0);
    if(fetch("is_supervisor","user","username",username).at(0)=="1") //if supervisor
    {
        bool isAdmin;
        if(fetch("is_admin","user","username",username).at(0)=="1")
            isAdmin=true;
        else
            isAdmin=false;
        Supervisor s = Supervisor(name, Login(username,password),isAdmin);

        // load up with employees
        QList<QString> employees = fetch("emp_username","supervises","Super_username",username);
        foreach(QString e,employees)
        {
            eName = fetch("name","user","username",e).at(0);
            eUser = fetch("username","user","username",e).at(0);
            ePass = fetch("password","user","username",e).at(0);
            Employee E = Employee(eName,Login(eUser,ePass));
            s.addEmployee(E);
        }
        s.printToDebug();
        emit openSupervisor(s);
    }
    else //if not supervisor, then employee
    {
        Employee e = Employee(name, Login(username,password));
        emit openEmployee(e);
    }
}

QList<Record> DatabaseHandler::getAllRecords(QList<Employee> employees)
{
    QList<Record> ret;
    foreach(Employee e, employees)
    {
        QList<QString> data = fetch("website","report","username",e.Username());
        foreach(QString d, data)
        {
            qDebug() << d;
        }
        QString website, time, date, category;
        QSqlQuery wq = QSqlQuery("SELECT website, time, date FROM report WHERE username='"+e.Username()+"'",m_db);

        while(wq.next())
        {
            website = wq.value(0).toString();
            time = wq.value(1).toString();
            date = wq.value(2).toString();
            category = getCategory(website);
            qDebug() << website+", "+time+", "+date+", "+category;
            Record r = Record(QDate::fromString(date,"yyyy-mm-dd"),time.toInt(),website,category);
            ret.append(r);
        }

    }
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

    if(!opened){ qDebug() << "remote database not opened"; }

    m_categories = new QFile("../URL-categorization-DFE.csv");
    fillCategories();
}

void DatabaseHandler::fillCategories()
{
    if(m_categories->open(QIODevice::ReadOnly))
    {
        int lineindex = 0;                     // file line counter
        QTextStream in(m_categories);                 // read to text stream

        while (!in.atEnd())
        {
            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();

            //skip the first line
            if(lineindex==0)
            {
                lineindex++;
                continue;
            }

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(",");

            websiteCategory_t wc = {lineToken.at(0), lineToken.at(1)};
            m_catMap.push_back(wc);

            lineindex++;
        }
        m_categories->close();
    }
    else
    {
        qDebug() << "Opening website csv error: "+m_categories->errorString();
    }
}

QString DatabaseHandler::getCategory(QString website)
{
    if(!m_catMap.isEmpty())
    {
        foreach(websiteCategory_t wc,m_catMap)
        {
            if(wc.wesbite == website)
            {
                return wc.category;
            }
        }
        qDebug() << "website not found in category map";
        return nullptr;
    }
    else
    {
        qDebug() << "website category map access attepted when map is empty";
        return nullptr;
    }
}

QList<QString> DatabaseHandler::fetch(QString attr, QString table, QString whereAttr, QString whereVal)
{
    QList<QString> ret;
    QSqlQuery query = QSqlQuery("SELECT "+attr+" FROM "+table+" WHERE "+whereAttr+"='"+whereVal+"'",m_db);
    //query.setForwardOnly(true); //this saves memory and overhead
    //query.prepare("SELECT "+attr+" FROM "+table+" WHERE "+whereAttr+"='"+whereVal+"'");

    qDebug() << query.lastError().text();

    while(query.next())
    {
        ret.append(query.value(0).toString());
    }
    return ret;
}

