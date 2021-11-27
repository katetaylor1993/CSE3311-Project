#include "user.h"

User::User(QString name, Login login, bool appAcc, bool admAcc) :
    m_name{name},
    m_login{Login(&login)},
    m_accessApp{appAcc},
    m_accessAdmin{admAcc}
{

}


QString User::Name() {return m_name;}

QString User::Username() {return m_login.Username();}

bool User::isSupervisor() {return m_accessApp;}

bool User::isAdmin() {return m_accessAdmin;}
