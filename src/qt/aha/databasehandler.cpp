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
{}

QString DatabaseHandler::attemptSignIn(QString username, QString password)
{
    QList<QString> pass = fetch("password","user","username",username);
    if(pass.isEmpty()) {return nullptr;}
    if(pass.at(0) == password){
        emit loggedIn(username);
        if(fetch("is_supervisor","user","username",username).at(0)=="1")
            return "supervisor";
        else
            return "employee";
    }
    else
    {
        emit badLoginInfo();
        return "badLogin";
    }
}

User * DatabaseHandler::getUserInfo(QString username)
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
        Supervisor * s = new Supervisor(name, Login(username,password),isAdmin);

        // load up with employees
        QList<QString> employees = fetch("emp_username","supervises","Super_username",username);
        foreach(QString e,employees)
        {
            eName = fetch("name","user","username",e).at(0);
            eUser = fetch("username","user","username",e).at(0);
            ePass = fetch("password","user","username",e).at(0);
            Employee E = Employee(eName,Login(eUser,ePass));
            s->addEmployee(E);
        }
        s->printToDebug();
        return dynamic_cast<User *>(s);
    }
    else //if not supervisor, then employee
    {
        Employee * e = new Employee(name, Login(username,password));
        return dynamic_cast<User *>(e);
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
            //qDebug() << d;
        }
        QString website, time, date, category;
        QSqlQuery wq = QSqlQuery("SELECT website, time, date FROM report WHERE username='"+e.Username()+"'",m_db);

        while(wq.next())
        {
            website = wq.value(0).toString();
            time = wq.value(1).toString();
            date = wq.value(2).toString();
            category = getCategory(website);
            //qDebug() << website+", "+time+", "+date+", "+category;
            Record r = Record(QDate::fromString(date,"yyyy-MM-dd"),time.toInt(),website,category,e.Name());
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

    QSqlQuery q = QSqlQuery("INSERT OR UPDATE record (username, website, date, time) VALUES ('emp4','www.github.com', '2021-11-19', 400",m_db);


    m_categories = new QFile("../URL-categorization-DFE.csv",this);
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

            m_catMap.insert(lineToken.at(0),lineToken.at(1));

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
        QString ret = m_catMap.value(website.remove("www."));
        return ret;
    }
    else
    {
        qDebug() << "website category map access attepted when map is empty";
        return nullptr;
    }
}

int DatabaseHandler::exportData(QString filename, QString employeeName)
{
    if(!filename.contains(".csv"))
        return 1;
    QFile file = QFile(filename);
    if(!(file.open(QIODevice::ReadOnly)))
        return 1;

    int lineindex = 0;                     // file line counter
    QTextStream in(&file);                 // read to text stream

    QSqlQuery q = QSqlQuery(m_db);
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
        QDate date = QDate::fromString(lineToken[1],"M/d/yyyy");
        QString dateStr = date.toString("yyyy-MM-dd");
        QString qstr = QString("INSERT INTO report (username, website, date, time) "
                               "VALUES ('"+employeeName+"','"+lineToken[0]+"', '"+dateStr+"', "+lineToken[2]+
                ") ON DUPLICATE KEY UPDATE time="+lineToken[2]+"");

        q.prepare(qstr);
        q.exec();
        //qDebug() << q.lastError().databaseText();
        //qDebug() << qstr;
    }
    return 0;
}

QList<QString> DatabaseHandler::fetch(QString attr, QString table, QString whereAttr, QString whereVal)
{
    QList<QString> ret;
    QSqlQuery query = QSqlQuery("SELECT "+attr+" FROM "+table+" WHERE "+whereAttr+"='"+whereVal+"'",m_db);
    //query.setForwardOnly(true); //this saves memory and overhead
    //query.prepare("SELECT "+attr+" FROM "+table+" WHERE "+whereAttr+"='"+whereVal+"'");

    //qDebug() << query.lastError().text();

    while(query.next())
    {
        ret.append(query.value(0).toString());
    }
    return ret;
}

