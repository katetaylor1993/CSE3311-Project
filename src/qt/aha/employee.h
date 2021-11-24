#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "user.h"

class Employee : public User
{
public:
    explicit Employee(QString name, Login login);
};

#endif // EMPLOYEE_H
