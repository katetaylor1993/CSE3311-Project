#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QDialog>

#include "databasehandler.h"
#include "login.h"

namespace Ui {
class LoginWin;
}

class LoginWin : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWin(DatabaseHandler * dbh, QWidget *parent = nullptr);
    ~LoginWin();

private slots:
    void on_pushButton_clicked();
    void handleOpenEmployee(Employee e);
    void handleOpenSupervisor(Supervisor s);
    void handleBadLoginInfo();

private:
    Ui::LoginWin *ui;
    DatabaseHandler *m_dbh;

signals:
    void currentUser(Login login);
};

#endif // LOGINWIN_H
