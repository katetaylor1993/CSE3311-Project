#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "user.h"
#include "employee.h"

class Supervisor : public User
{
public:
    Supervisor();
    Supervisor(QString name, Login login, bool admin);
    QList<Employee> m_employees;
    void addEmployee(Employee e);

    //debug stuff
    void printToDebug();
};

#endif // SUPERVISOR_H
