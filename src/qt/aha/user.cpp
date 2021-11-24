#include "user.h"

User::User(QString name, Login login, bool appAcc, bool admAcc) :
    m_name{name},
    m_login{Login(&login)},
    m_accessApp{appAcc},
    m_accessAdmin{admAcc}
{

}

Employee::Employee(QString name, Login login) :
    User(name, Login(&login), false, false)
{}

Supervisor::Supervisor(QString name, Login login, bool admin) :
    User(name, Login(&login),true, admin)
{}


