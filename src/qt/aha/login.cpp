#include "login.h"

Login::Login(QString username, QString password) :
    m_username{username},
    m_password{password}
{

}

Login::Login(Login * original) :
    m_username(original->m_username),
    m_password(original->m_password)
{}
