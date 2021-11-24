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

#endif // USER_H
