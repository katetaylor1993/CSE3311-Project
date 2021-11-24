#include "mainwin.h"
#include "loginwin.h"
#include "databasehandler.h"

#include <QApplication>
#include <QFile>

DatabaseHandler * DatabaseHandler::obj;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DatabaseHandler::getInstance()->connectToDB();

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
