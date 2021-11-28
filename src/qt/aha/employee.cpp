#include "employee.h"

Employee::Employee(QString name, Login login) :
    User(name, Login(&login), false, false)
{}

Employee::Employee() :
    User("",Login("",""),true,false)
{}
