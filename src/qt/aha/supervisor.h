#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "user.h"
#include "employee.h"

class Supervisor : public User
{
public:
    explicit Supervisor(QString name, Login login, bool admin);
    QList<Employee> m_employees;
};

#endif // SUPERVISOR_H
