#include "loginwin.h"
#include "ui_loginwin.h"
#include <QMessageBox>

LoginWin::LoginWin(DatabaseHandler * dbh, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWin),
    m_dbh{dbh}
{
    ui->setupUi(this);

    //this->showMaximized();
    this->setWindowState(Qt::WindowMaximized);
}

LoginWin::~LoginWin()
{
    delete ui;
}

void LoginWin::on_pushButton_clicked()
{
    QString user = ui->lineEdit_userName->text();
    QString pass = ui->lineEdit_password->text();
    connect(m_dbh,SIGNAL(badLoginInfo()),this,SLOT(handleBadLoginInfo()));

    QString signInSuccess = m_dbh->attemptSignIn(user,pass);

    if(signInSuccess == "supervisor")
    {
        this->done(1);
    }
    else if(signInSuccess == "employee")
    {
        this->done(2);
    }
}

void LoginWin::handleBadLoginInfo()
{
    QMessageBox::warning(this,"Login","Username and password combination is not correct.");
}

void LoginWin::handleOpenEmployee(Employee e)
{
    this->accept();
}

void LoginWin::handleOpenSupervisor(Supervisor s)
{
    this->accept();
}

