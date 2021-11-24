#include "supervisor.h"

Supervisor::Supervisor(QString name, Login login, bool admin) :
    User(name, Login(&login),true, admin)
{}
