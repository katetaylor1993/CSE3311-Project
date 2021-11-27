#include "mainwin.h"
#include "loginwin.h"
#include "databasehandler.h"

#include <iostream>
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QStyleOptionTitleBar>
#include<QDebug>


DatabaseHandler * DatabaseHandler::obj;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DatabaseHandler::getInstance()->connectToDB();

    MainWin w;

    w.setWindowState(Qt::WindowMaximized);
    w.setWindowTitle("Aha");
    w.show();

    return app.exec();
}
