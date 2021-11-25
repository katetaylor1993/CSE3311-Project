#include "loginwin.h"
#include "ui_loginwin.h"
#include <QMessageBox>

LoginWin::LoginWin(DatabaseHandler * dbh, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWin),
    m_dbh{dbh}
{
    ui->setupUi(this);
    connect(m_dbh, SIGNAL(userSignedIn()),this, SLOT(loginSuccess()));
    DatabaseHandler::getInstance()->getUserInfo("super1");
}

LoginWin::~LoginWin()
{
    delete ui;
}

void LoginWin::on_pushButton_clicked()
{
    QString user = ui->lineEdit_userName->text();
    QString pass = ui->lineEdit_password->text();

    bool signInSuccess = m_dbh->attemptSignIn(user,pass);

    if(signInSuccess)
    {
        this->done(1);
    }
    else
    {
        QMessageBox::warning(this,"Login","Username and password combination is not correct.");
    }
}

void LoginWin::loginSuccess()
{
    QString user = ui->lineEdit_userName->text();
    QString pass = ui->lineEdit_password->text();
    emit currentUser(Login(user,pass));
    this->done(1);
}

