#ifndef USER_H
#define USER_H

#include <QObject>

#include "login.h"

class User
{
public:
    explicit User(QString name, Login login, bool appAcc, bool admAcc);
    bool isAdmin();
    bool isSupervisor();

private:
    QString m_name;
    Login m_login;
    bool m_accessApp;
    bool m_accessAdmin;

};

class Employee : public User
{
public:
    explicit Employee(QString name, Login login);
};

class Supervisor : public User
{
public:
    explicit Supervisor(QString name, Login login, bool admin);
    void addEmployee(Employee toAdd);

private:
    QList<Employee> m_employees;
};

#endif // USER_H
