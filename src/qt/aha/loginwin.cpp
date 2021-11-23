#include "loginwin.h"
#include "ui_loginwin.h"
#include <QMessageBox>

LoginWin::LoginWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWin)
{
    ui->setupUi(this);
    this->setStyleSheet("{background-image:url(:/image/image/bg.png);}");
}

LoginWin::~LoginWin()
{
    delete ui;
}

void LoginWin::on_pushButton_clicked()
{
    QString user = ui->lineEdit_userName->text();
    QString pass = ui->lineEdit_password->text();

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

