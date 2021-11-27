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
    connect(m_dbh,SIGNAL(openEmployee(Employee)),this,SLOT(handleOpenEmployee(Employee)));
    connect(m_dbh, SIGNAL(openSupervisor(Supervisor)),this,SLOT(handleOpenSupervisor(Supervisor)));

    bool signInSuccess = m_dbh->attemptSignIn(user,pass);

    if(signInSuccess)
    {
        connect(m_dbh,SIGNAL(openEmployee(Employee)),this,SLOT(handleOpenEmployee(Employee)));
        connect(m_dbh, SIGNAL(openSupervisor(Supervisor)),this,SLOT(handleOpenSupervisor(Supervisor)));
        m_dbh->getUserInfo(user);
    }
    else
    {
        QMessageBox::warning(this,"Login","Something went wrong");
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

