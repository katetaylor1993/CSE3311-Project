#include "supervisor.h"
#include <QDebug>

Supervisor::Supervisor(QString name, Login login, bool admin) :
    User(name, Login(&login),true, admin)
{}

void Supervisor::printToDebug()
{
    qDebug() << "PRINTING SUPERVISOR INFO";
    qDebug() << "Name: "+this->m_name;
    qDebug() << "User: "+this->m_login.Username();
    qDebug() << "EMPLOYEES UNDER THIS SUPERVISOR";
    foreach(Employee e,m_employees)
    {
        qDebug() << e.Name();
    }
}

void Supervisor::addEmployee(Employee e)
{
    m_employees.append(e);
}
