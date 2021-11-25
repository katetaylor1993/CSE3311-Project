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

    connect(m_dbh, SIGNAL(userSignedIn()),this, SLOT(loginSuccess()));
    Employee one = Employee("Jane Doe",Login("emp1","Password123"));
    Employee two = Employee("John Doe", Login("emp2","Password123"));
    QList<Employee> temp;
    temp.append(one);
    temp.append(two);
    m_dbh->getAllRecords(temp);

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

