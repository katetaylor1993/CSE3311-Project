#include "mainwin.h"
#include "loginwin.h"
#include "databasehandler.h"

#include <QApplication>
#include <QFile>
#include <QStyleOptionTitleBar>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DatabaseHandler dbhandler;

    MainWin w;

    w.setWindowState(Qt::WindowMaximized);
    w.setWindowTitle("Aha");
    w.show();
    return app.exec();
}
