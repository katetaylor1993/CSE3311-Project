#include "mainwin.h"
#include "loginwin.h"
#include "databasehandler.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DatabaseHandler dbHandler;
    dbHandler.setAPIKey("AIzaSyD_xlNz0ZkNP0GMwpBEgpvVudJb4v0v6Z8");
    //dbHandler.signUserUp( "NewUser54Email@gmail.com", "Password123!");
    //dbHandler.signUserIn( "C55@gmail.com", "Password123!");

    MainWin w;

    //set the app syle sheet
    QFile styleSheetFile(":/style/style/Toolery/Toolery.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet{QLatin1String (styleSheetFile.readAll())};
    app.setStyleSheet(styleSheet);


    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return app.exec();
}
