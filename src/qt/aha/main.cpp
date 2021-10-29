#include <QGuiApplication>
#include <QQmlApplicationEngine>


/*
  ******************** HEEEY!! LOOK HERE!! ********************
  BEFORE YOU START:
    1. Are you on your own branch on git? Current branch should
        NOT be "main"
    2. Keep things looking neat and uniform
    3. I may put more stuff here so check back after pull
  */

#include "controller.h"

// Singleton pattern. No touchy.
Controller * Controller::obj;
static Controller * ctrl = Controller::getInstance();

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // I have to fix this later to get controller to work. It's 1.30AM.
    // engine.rootContext()->setContextProperty("ctrl", &ctrl);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
