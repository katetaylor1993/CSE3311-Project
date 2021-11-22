#include "mainwin.h"
#include "loginwin.h"
#include "databasehandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseHandler dbhandler;
    MainWin w;
    w.show();
    return a.exec();
}
