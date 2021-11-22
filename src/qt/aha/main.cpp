#include "mainwin.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

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
