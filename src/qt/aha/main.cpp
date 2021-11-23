#include "mainwin.h"
#include "databasehandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseHandler dbHandler;
    dbHandler.setAPIKey("AIzaSyD_xlNz0ZkNP0GMwpBEgpvVudJb4v0v6Z8");
    //dbHandler.signUserUp( "NewUser54Email@gmail.com", "Password123!");
    //dbHandler.signUserIn( "C55@gmail.com", "Password123!");
    MainWin w;
    w.show();
    return a.exec();
}
