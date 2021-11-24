#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QDialog>

#include "databasehandler.h"

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

private:
    Ui::LoginWin *ui;
    DatabaseHandler *m_dbh;
};

#endif // LOGINWIN_H
