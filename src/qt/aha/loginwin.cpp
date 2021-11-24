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
}

LoginWin::~LoginWin()
{
    delete ui;
}

void LoginWin::on_pushButton_clicked()
{
    QString user = ui->lineEdit_userName->text();
    QString pass = ui->lineEdit_password->text();

    //m_dbh->signUserIn(user, pass);

    //TODO: This needs to be a real verification of user and pass
    if(user == "test" && pass == "test")
    {
        //pass back to parent info needed to log in
        // TODO: This should pass back the id of the user that is logging in instead of 1
        this->done(1);
        // this is a test comment!
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

