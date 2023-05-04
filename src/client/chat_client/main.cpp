#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/Socket/Socket.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    //events before engine load url
//    qmlRegisterType<Client>("mycpp.Client",1,0,"Client");
    Client the_Client;//set global variable
    the_Client.connect("127.0.0.1",8888);
    engine.rootContext()->setContextProperty("$Client",&the_Client);
    engine.load(url);
    return app.exec();
}
