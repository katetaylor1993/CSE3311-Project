#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>

class Login
{
public:
    Login(QString username, QString password);
    Login(Login * original);
    QString Username();

private:
    QString m_username;
    QString m_password;

};

#endif // LOGIN_H
