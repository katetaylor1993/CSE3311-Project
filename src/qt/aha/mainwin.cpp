#include "mainwin.h"
#include "ui_mainwin.h"
#include "loginwin.h"

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    // first, user needs to login
    LoginWin * login = new LoginWin(this);
    m_currentUser = login->exec();

    //check that user is valid before launching the window
    if(m_currentUser == 1)
    {
        ui->setupUi(this);
    }
    else
    {
        // since this is the top-level window, closing it will cause
        // app to quit
        this->close();
    }
}

MainWin::~MainWin()
{
    delete ui;
}

